#pragma once
#include "nonCopyable.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"
#include "hashedWordList.H"
#include "fluidThermo.H"

    namespace 
Foam
{
    class porousMedia;

    class 
geochemistryModel
    : public nonCopyable
{
        porousMedia& 
    parent_;

protected:
        fluidThermo const& 
    fluidThermo_;

public:
    TypeName ("geochemistry");

    declareRunTimeSelectionTable (
          autoPtr
        , geochemistryModel
        , dictionary
        , (fvMesh const& mesh, porousMedia& parent)
        , (mesh, parent)
    );
        static autoPtr<geochemistryModel> 
    New (fvMesh const& mesh, porousMedia& parent);

    geochemistryModel (fvMesh const& mesh, porousMedia& parent);

        virtual 
    ~geochemistryModel ()
    {}

        auto& 
    parent ()
    {
        return parent_;
    }

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
