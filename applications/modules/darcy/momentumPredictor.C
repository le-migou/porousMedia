#include "darcy.H"
#include "fvcGrad.H"
#include "fvmSup.H"

// Modified from applications/modules/isothermalFluid/momentumPredictor.C
void Foam::solvers::darcy::momentumPredictor()
{
    volVectorField& U(U_);

    tUEqn =
    (
        fvm::ddt(rho, U) // + fvm::div(phi, U)
      + MRF.DDt(rho, U)
      // + momentumTransport->divDevTau(U)
      - fvm::Sp (muInvK_, U)
     ==
        fvModels().source(rho, U)
    );
    fvVectorMatrix& UEqn = tUEqn.ref();

    UEqn.relax();

    fvConstraints().constrain(UEqn);

    if (pimple.momentumPredictor())
    {
        if (buoyancy.valid())
        {
            solve
            (
                UEqn
             ==
                netForce()
            );
        }
        else
        {
            solve(UEqn == -fvc::grad(p));
        }

        fvConstraints().constrain(U);
        K = 0.5*magSqr(U);
    }
}
