#include "darcy.H"
#include "constrainHbyA.H"
#include "constrainPressure.H"
#include "adjustPhi.H"
#include "fvcMeshPhi.H"
#include "fvcFlux.H"
#include "fvcDdt.H"
#include "fvcGrad.H"
#include "fvcSnGrad.H"
#include "fvcReconstruct.H"
#include "fvcVolumeIntegrate.H"
#include "fvmDiv.H"
#include "fvmLaplacian.H"

// Modified from applications/modules/isothermalFluid/correctPressure.C
void Foam::solvers::darcy::continuityErrors()
{
    fluidSolver::continuityErrors(rho, thermo.rho(), phi);
}

void Foam::solvers::darcy::correctPressure()
{
    volScalarField& rho(rho_);
    volScalarField& p(p_);
    volVectorField& U(U_);
    surfaceScalarField& phi(phi_);

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

    volVectorField HbyA(constrainHbyA(rAU*UEqn.H(), U, p));

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

    bool adjustMass = false;

    if (pimple.transonic())
    {
        const surfaceScalarField phidByPsi
        (
            constrainPhid
            (
                fvc::relative(phiHbyA, rho, U)/rhof,
                p
            )
        );

        const surfaceScalarField phid("phid", fvc::interpolate(psi)*phidByPsi);

        // Subtract the compressible part
        // The resulting flux will be zero for a perfect gas
        phiHbyA -= fvc::interpolate(psi*p)*phidByPsi;

        if (pimple.consistent())
        {
            phiHbyA += (rhorAAtUf - rhorAUf)*fvc::snGrad(p)*mesh.magSf();
            HbyA += (rAAtU - rAU)*fvc::grad(p);
        }

        // Update the pressure BCs to ensure flux consistency
        constrainPressure(p, rho, U, phiHbyA, rhorAAtUf, MRF);

        fvc::makeRelative(phiHbyA, rho, U);

        fvScalarMatrix pDDtEqn
        (
            fvc::ddt(rho) + psi*correction(fvm::ddt(p))
          + fvc::div(phiHbyA) + fvm::div(phid, p)
         ==
            fvModels().sourceProxy(rho, p)
        );

        while (pimple.correctNonOrthogonal())
        {
            fvScalarMatrix pEqn(pDDtEqn - fvm::laplacian(rhorAAtUf, p));

            // Relax the pressure equation to ensure diagonal-dominance
            pEqn.relax();

            pEqn.setReference
            (
                pressureReference.refCell(),
                pressureReference.refValue()
            );

            fvConstraints().constrain(pEqn);

            pEqn.solve();

            if (pimple.finalNonOrthogonalIter())
            {
                phi = phiHbyA + pEqn.flux();
            }
        }
    }
    else
    {
        if (pimple.consistent())
        {
            phiHbyA += (rhorAAtUf - rhorAUf)*fvc::snGrad(p)*mesh.magSf();
            HbyA += (rAAtU - rAU)*fvc::grad(p);
        }

        // Update the pressure BCs to ensure flux consistency
        constrainPressure(p, rho, U, phiHbyA, rhorAAtUf, MRF);

        fvc::makeRelative(phiHbyA, rho, U);

        if (mesh.schemes().steady())
        {
            adjustMass = adjustPhi(phiHbyA, U, p);
        }

        fvScalarMatrix pDDtEqn
        (
            fvc::ddt(rho) + psi*correction(fvm::ddt(p))
          + fvc::div(phiHbyA)
         ==
            fvModels().sourceProxy(rho, p)
        );

        while (pimple.correctNonOrthogonal())
        {
            fvScalarMatrix pEqn(pDDtEqn - fvm::laplacian(rhorAAtUf, p));

            pEqn.setReference
            (
                pressureReference.refCell(),
                pressureReference.refValue()
            );

            fvConstraints().constrain(pEqn);

            pEqn.solve();

            if (pimple.finalNonOrthogonalIter())
            {
                phi = phiHbyA + pEqn.flux();
            }
        }
    }

    if (!mesh.schemes().steady())
    {
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

    // Explicitly relax pressure for momentum corrector
    p.relax();

    //U = HbyA - rAAtU*fvc::grad(p);
    U = fvc::reconstruct (phi / rhof);
    U.correctBoundaryConditions();
    fvConstraints().constrain(U);
    K = 0.5*magSqr(U);

    if (mesh.schemes().steady())
    {
        fvConstraints().constrain(p);
    }

    // For steady compressible closed-volume cases adjust the pressure level
    // to obey overall mass continuity
    if (adjustMass && !thermo.incompressible())
    {
        p += (initialMass - fvc::domainIntegrate(thermo.rho()))
            /fvc::domainIntegrate(psi);
        p.correctBoundaryConditions();
    }

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

    updatePorousMedium();
}
