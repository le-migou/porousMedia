#include "darcy.H"
#include "constrainHbyA.H"
#include "constrainPressure.H"
#include "adjustPhi.H"
#include "fvcMeshPhi.H"
#include "fvcFlux.H"
#include "fvcDdt.H"
#include "fvcSnGrad.H"
#include "fvcReconstruct.H"
#include "fvcVolumeIntegrate.H"
#include "fvmDiv.H"
#include "fvmLaplacian.H"

// Modified from applications/modules/isothermalFluid/correctBuoyantPressure.C
void Foam::solvers::darcy::correctBuoyantPressure()
{
    volScalarField& rho(rho_);
    volScalarField& p(p_);
    volVectorField& U(U_);
    surfaceScalarField& phi(phi_);

    // Local references to the buoyancy parameters
    const volScalarField& gh = buoyancy->gh;
    const surfaceScalarField& ghf = buoyancy->ghf;
    const uniformDimensionedScalarField pRef = buoyancy->pRef;

    const volScalarField& psi = thermo.psi();
    rho = thermo.rho();
    rho.relax();

    fvVectorMatrix& UEqn = tUEqn.ref();

    // Thermodynamic density needs to be updated by psi*d(p) after the
    // pressure solution
    const volScalarField psip0(psi*p);

    const surfaceScalarField rhof(fvc::interpolate(rho));

    const volScalarField rAU("rAU", 1.0/UEqn.A());
    const surfaceScalarField rhorAUf("rhorAUf", fvc::interpolate(rho*rAU));

    tmp<volScalarField> rAtU
    (
        pimple.consistent()
      ? volScalarField::New("rAtU", 1.0/(1.0/rAU - UEqn.H1()))
      : tmp<volScalarField>(nullptr)
    );

    tmp<surfaceScalarField> rhorAtUf
    (
        pimple.consistent()
      ? surfaceScalarField::New("rhoRAtUf", fvc::interpolate(rho*rAtU()))
      : tmp<surfaceScalarField>(nullptr)
    );

    const volScalarField& rAAtU = pimple.consistent() ? rAtU() : rAU;
    const surfaceScalarField& rhorAAtUf =
        pimple.consistent() ? rhorAtUf() : rhorAUf;

    volVectorField HbyA(constrainHbyA(rAU*UEqn.H(), U, p_rgh));

    if (pimple.nCorrPiso() <= 1)
    {
        tUEqn.clear();
    }

    surfaceScalarField phiHbyA
    (
        "phiHbyA",
        rhof*fvc::flux(HbyA)
      + rhorAUf*fvc::ddtCorr(rho, U, phi, rhoUf)
    );

    MRF.makeRelative(rhof, phiHbyA);

    const bool adjustMass =
        mesh.schemes().steady() && adjustPhi(phiHbyA, U, p_rgh);

    const surfaceScalarField ghGradRhof(-ghf*fvc::snGrad(rho)*mesh.magSf());

    phiHbyA += rhorAUf*ghGradRhof;

    tmp<fvScalarMatrix> tp_rghEqn;

    if (pimple.transonic())
    {
        const surfaceScalarField phidByPsi
        (
            constrainPhid
            (
                fvc::relative(phiHbyA, rho, U)/rhof,
                p_rgh
            )
        );

        const surfaceScalarField phid("phid", fvc::interpolate(psi)*phidByPsi);

        // Subtract the compressible part
        // The resulting flux will be zero for a perfect gas
        phiHbyA -= fvc::interpolate(psi*p_rgh)*phidByPsi;

        if (pimple.consistent())
        {
            const surfaceScalarField gradpf(fvc::snGrad(p_rgh)*mesh.magSf());
            phiHbyA += (rhorAAtUf - rhorAUf)*gradpf;
            HbyA += (rAAtU - rAU)*fvc::reconstruct(gradpf - ghGradRhof);
        }

        // Update the pressure BCs to ensure flux consistency
        constrainPressure(p_rgh, rho, U, phiHbyA, rhorAAtUf, MRF);

        fvc::makeRelative(phiHbyA, rho, U);

        fvScalarMatrix p_rghDDtEqn
        (
            fvc::ddt(rho) + psi*correction(fvm::ddt(p_rgh))
          + fvc::div(phiHbyA) + fvm::div(phid, p_rgh)
         ==
            fvModels().sourceProxy(rho, p_rgh)
        );

        while (pimple.correctNonOrthogonal())
        {
            tp_rghEqn = p_rghDDtEqn - fvm::laplacian(rhorAAtUf, p);
            fvScalarMatrix& p_rghEqn = tp_rghEqn.ref();

            // Relax the pressure equation to ensure diagonal-dominance
            p_rghEqn.relax();

            p_rghEqn.setReference
            (
                pressureReference.refCell(),
                pressureReference.refValue()
            );

            fvConstraints().constrain(p_rghEqn);

            p_rghEqn.solve();
        }
    }
    else
    {
        if (pimple.consistent())
        {
            const surfaceScalarField gradpf(fvc::snGrad(p_rgh)*mesh.magSf());
            phiHbyA += (rhorAAtUf - rhorAUf)*gradpf;
            HbyA += (rAAtU - rAU)*fvc::reconstruct(gradpf - ghGradRhof);
        }

        // Update the pressure BCs to ensure flux consistency
        constrainPressure(p_rgh, rho, U, phiHbyA, rhorAAtUf, MRF);

        fvc::makeRelative(phiHbyA, rho, U);

        fvScalarMatrix p_rghDDtEqn
        (
            fvc::ddt(rho) + psi*correction(fvm::ddt(p_rgh))
          + fvc::div(phiHbyA)
         ==
            fvModels().sourceProxy(rho, p_rgh)
        );

        while (pimple.correctNonOrthogonal())
        {
            tp_rghEqn = p_rghDDtEqn - fvm::laplacian(rhorAAtUf, p_rgh);
            fvScalarMatrix& p_rghEqn = tp_rghEqn.ref();

            p_rghEqn.setReference
            (
                pressureReference.refCell(),
                pressureReference.refValue()
            );

            fvConstraints().constrain(p_rghEqn);

            p_rghEqn.solve();
        }
    }

    const fvScalarMatrix& p_rghEqn = tp_rghEqn();

    phi = phiHbyA + p_rghEqn.flux();

    // Calculate and relax the net pressure-buoyancy force
    netForce.ref().relax
    (
        fvc::reconstruct((ghGradRhof + p_rghEqn.flux()/rhorAAtUf)),
        p_rgh.relaxationFactor()
    );

    // Correct the momentum source with the pressure gradient flux
    // calculated from the relaxed pressure
    //U = HbyA + rAAtU*netForce();
    U = fvc::reconstruct (phi / rhof);
    U.correctBoundaryConditions();
    fvConstraints().constrain(U);

    K = 0.5*magSqr(U);

    if (!mesh.schemes().steady())
    {
        p = p_rgh + rho*gh + pRef;

        const bool constrained = fvConstraints().constrain(p);

        // Thermodynamic density update
        thermo_.correctRho(psi*p - psip0);

        if (constrained)
        {
            rho = thermo.rho();
        }

        correctDensity();
    }

    continuityErrors();

    p = p_rgh + rho*gh + pRef;

    if (mesh.schemes().steady())
    {
        if (fvConstraints().constrain(p))
        {
            p_rgh = p - rho*gh - pRef;
            p_rgh.correctBoundaryConditions();
        }
    }

    // For steady compressible closed-volume cases adjust the pressure level
    // to obey overall mass continuity
    if (adjustMass && !thermo.incompressible())
    {
        p += (initialMass - fvc::domainIntegrate(thermo.rho()))
            /fvc::domainIntegrate(psi);
        p_rgh = p - rho*gh - pRef;
        p_rgh.correctBoundaryConditions();
    }

    // Optionally relax pressure for the thermophysics
    p.relax();

    if (mesh.schemes().steady() || pimple.simpleRho() || adjustMass)
    {
        rho = thermo.rho();
    }

    if (mesh.schemes().steady() || pimple.simpleRho())
    {
        rho.relax();
    }

    // Correct rhoUf if the mesh is moving
    fvc::correctRhoUf(rhoUf, rho, U, phi, MRF);

    if (thermo.dpdt())
    {
        dpdt = fvc::ddt(p);
    }

    updatePorousMedia();
}
