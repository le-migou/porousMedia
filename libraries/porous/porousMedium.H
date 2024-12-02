#pragma once
#include "IOdictionary.H"
#include "geochemistryModel.H"
#include "absolutePermeabilityModel.H"
#include "uniformDimensionedFields.H"
#include "soluteMediumList.H"
#include "mineralMediumList.H"
#include "soluteMineralPairList.H"
#include "isothermalFluid.H"

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
        soluteMineralPairList
    soluteMineralPairList_;
    
    // The thermo-physical package for the pure fluid.
    // It is here because it is it who owns the pressure fields (for some
    // reasons)
        autoPtr <fluidThermo> 
    fluidThermo_;
        autoPtr <geochemistryModel> 
    geochemistryModel_;
        autoPtr <absolutePermeabilityModel> 
    absolutePermeabilityModel_;
        uniformDimensionedVectorField 
    g_;

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
        auto
    mesh () const
        -> fvMesh const&
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
        auto& 
    solutes ()
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
        auto& 
    mineral (label mineralIndex)
    {
        return mineralList_[mineralIndex];
    }
        auto const&
    soluteMineralPairs () const
    {
        return soluteMineralPairList_;
    }
        auto&
    soluteMineralPairs ()
    {
        return soluteMineralPairList_;
    }
        auto const&
    soluteMineralPair (label soluteIndex, label mineralIndex) const
    {
        return soluteMineralPairList_ (soluteIndex, mineralIndex);
    }
        auto&
    soluteMineralPair (label soluteIndex, label mineralIndex)
    {
        return soluteMineralPairList_ (soluteIndex, mineralIndex);
    }

    // Update the properties after a new velocity field has been computed
        void
    update ();

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

    // Gravitational acceleration
        auto const& 
    g () const
    {
        return g_;
    }
};
} // namespace Foam
