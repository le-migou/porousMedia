#include "darcy.H"
#include "fvcDiv.H"

// Copy of applications/modules/isothermalFluid/correctDensity.C
void Foam::solvers::darcy::correctDensity()
{
    volScalarField& rho(rho_);

    fvScalarMatrix rhoEqn
    (
        fvm::ddt(rho) + fvc::div(phi)
      ==
        fvModels().source(rho)
    );

    fvConstraints().constrain(rhoEqn);

    rhoEqn.solve();

    fvConstraints().constrain(rho);
}
