#pragma once
#include "modelBase.H"
#include "runtimeSelection.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"
#include "fluidThermo.H"

    namespace 
Foam
{
    class porousMedium;

    class 
geochemistryModel
    : public modelBase
{
protected:
        fluidThermo const& 
    fluidThermo_;

public:
    TypeName ("geochemistryModel");
    OPENFOAM_RTS_MODEL_DECLARATION(geochemistryModel)

    geochemistryModel (
          fvMesh       const& mesh
        , porousMedium      & porous_medium // !
        , word         const& name
    );

    // Porosity
        virtual volScalarField const& 
    porosity () const = 0;

    // Density of the fluid
        virtual volScalarField const& 
    density () const = 0;

    // Viscosity of the fluid
        virtual volScalarField const& 
    dynamic_viscosity () const = 0;
};

} // namespace Foam
