#pragma once
#include "nonCopyable.H"
#include "IOdictionary.H"
#include "geochemistryModel.H"
#include "absolutePermeabilityModel.H"
#include "uniformDimensionedFields.H"
#include "solute.H"

    namespace 
Foam
{
    class fvMesh;

    class 
porousMedia
    : public nonCopyable
{       
    // Our link to OpenFOAM
        IOdictionary 
    dict_;
    
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
        PtrList <solute>
    solutes_;

public:
    TypeName ("porousMedia");

    porousMedia (const fvMesh& mesh);

    // virtual because this class might become a base class for other kinds of
    // porous media.
        virtual 
    ~porousMedia ()
    {}

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
        auto const& 
    thermo () const
    {
        return *fluidThermo_;
    }
        auto const& 
    solutes () const
    {
        return solutes_;
    }
        auto& 
    soluteConcentration (label soluteIndex) 
    {
        return solutes_[soluteIndex].concentration ();
    }

    // Update the properties after a new velocity field has been computed
        void
    update ()
    {
        geochemistryModel_->update ();
    }

    // Pressure
        auto& 
    p ()
    {
        return fluidThermo_->p ();
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
        auto const& 
    massSourceTerm () const
    {
        return geochemistryModel_->massSourceTerm ();
    }

    // Gravitational acceleration
        auto const& 
    g () const
    {
        return g_;
    }
};
} // namespace Foam
