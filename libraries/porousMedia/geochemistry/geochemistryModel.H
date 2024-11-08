#pragma once
#include "modelBase.H"
#include "runtimeSelection.H"
#include "nonCopyable.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"
#include "fluidThermo.H"

    namespace 
Foam
{
    class porousMedia;

    class 
geochemistryModel
    : public nonCopyable
    , public modelBase <porousMedia>
{
protected:
        fluidThermo const& 
    fluidThermo_;

public:
    TypeName ("geochemistryModel");
    OPENFOAM_RUNTIME_SELECTOR_DECLARATION(geochemistryModel)

    geochemistryModel (
          fvMesh const& mesh
        , porousMedia& parent
        , word const& name
    );

        virtual 
    ~geochemistryModel ()
    {}


    // Porosity
        virtual volScalarField const& 
    eps () const = 0;

    // Density of the fluid
        virtual volScalarField const& 
    rho () const = 0;

    // Viscosity of the fluid
        virtual volScalarField const& 
    mu () const = 0;

    // Source term for the flow solver
        virtual volScalarField const& 
    massSourceTerm () const = 0;

    // Update properties after a new velocity field  has been computed
        virtual void 
    update () = 0;
};

} // namespace Foam
