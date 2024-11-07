#include "darcy.H"
#include "addToRunTimeSelectionTable.H"

    namespace 
Foam
{
    namespace 
solvers
{
    defineTypeNameAndDebug (darcy, 0);
    addToRunTimeSelectionTable (solver, darcy, fvMesh);
}
}

// Copy of Foam::solvers::isothermalFluid::pressureCorrector()
void Foam::solvers::darcy::pressureCorrector()
{
    while (pimple.correct())
    {
        if (buoyancy.valid())
        {
            correctBuoyantPressure();
        }
        else
        {
            correctPressure();
        }
    }

    tUEqn.clear();
}
