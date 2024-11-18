#pragma once
#include "nonCopyable.H"
#include "IOdictionary.H"
#include "geochemistryModel.H"
#include "absolutePermeabilityModel.H"
#include "uniformDimensionedFields.H"
#include "soluteMediumList.H"
#include "mineralMediumList.H"
#include "isothermalFluid.H"

#define POROUS_MEDIA_REQUIRES_SOLUTE_MODEL(MODEL) \
forAll(parent_.solutes (), i)                     \
{                                                 \
    parent.solute (i).init_model_##MODEL ();      \
}

    namespace 
Foam
{
    class fvMesh;

    class 
porousMedium
    : public nonCopyable
{       
        solvers::isothermalFluid const&
    solver_;
        IOdictionary 
    dict_;
        fvMesh const&
    mesh_;

        soluteMediumList
    soluteList_;
        mineralMediumList
    mineralList_;
    
    // The thermo-physical package for the pure fluid.
    // It is here because it is it who owns the pressure fields (for some
    // reasons)
        autoPtr<fluidThermo> 
    fluidThermo_;
        autoPtr <geochemistryModel> 
    geochemistryModel_;
        autoPtr <absolutePermeabilityModel> 
    absolutePermeabilityModel_;
        uniformDimensionedVectorField 
    g_;
    /*
        PtrList <soluteMedium>
    solutes_;
    */

public:
    TypeName ("porousMedium");

    porousMedium (const fvMesh& mesh, solvers::isothermalFluid const& solver);

        virtual
    ~porousMedium () = default;

        auto& 
    dict ()
    {
        return dict_;
    }
        auto const& 
    dict () const
    {
        return dict_;
    }
        auto& 
    mesh ()
    {
        return mesh_;
    }
        auto const& 
    mesh () const
    {
        return mesh_;
    }
        auto const& 
    thermo () const
    {
        return *fluidThermo_;
    }
        auto const& 
    solutes () const
    {
        return soluteList_;
    }
        auto const& 
    solute (label soluteIndex) const
    {
        return soluteList_[soluteIndex];
    }
        auto& 
    solute (label soluteIndex)
    {
        return soluteList_[soluteIndex];
    }
        const auto& 
    soluteConcentration (label soluteIndex) const
    {
        return soluteList_[soluteIndex].concentration ();
    }
        auto& 
    soluteConcentration (label soluteIndex) 
    {
        return soluteList_[soluteIndex].concentration ();
    }

        auto const& 
    minerals () const
    {
        return mineralList_;
    }
        auto const& 
    mineral (label mineralIndex) const
    {
        return mineralList_[mineralIndex];
    }

    // Update the properties after a new velocity field has been computed
        void
    update ()
    {
        geochemistryModel_->update ();
    }

    // Pressure
        auto const& 
    p () const
    {
        return fluidThermo_->p ();
    }
    // Velocity
       auto const&
    U () const
    {
        return solver_.U;
    }
    // Velocity (flux at the faces)
       auto const&
    phi () const
    {
        return solver_.phi;
    }

    // Porosity
        auto const& 
    eps () const
    {
        return geochemistryModel_->eps ();
    }

    // Absolute permeability
        auto const& 
    K () const
    {
        return absolutePermeabilityModel_->K ();
    }

    // Density of the fluid
        auto const& 
    rho () const
    {
        return geochemistryModel_->rho ();
    }

    // Viscosity of the fluid
        auto const& 
    mu () const
    {
        return geochemistryModel_->mu ();
    }

    // Source term for the flow solver
    /*
        auto const& 
    massSourceTerm () const
    {
        return geochemistryModel_->massSourceTerm ();
    }
    */

    // Gravitational acceleration
        auto const& 
    g () const
    {
        return g_;
    }
};
} // namespace Foam
