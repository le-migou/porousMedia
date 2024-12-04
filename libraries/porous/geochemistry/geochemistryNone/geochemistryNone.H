#pragma once
#include "geochemistryModel.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

    class 
geochemistryNone
    : public geochemistryModel
{
        dimensionedScalar 
    initial_porosity_;
        volScalarField 
    porosity_;

public:

    TypeName ("geochemistryNone");

    geochemistryNone (
          fvMesh       const& mesh
        , porousMedium      & porous_media
        , word         const& name = "geochemistryNone"
    );

        volScalarField const& 
    porosity () const override
    {
        return porosity_;
    }
        volScalarField const& 
    density () const override
    {
        return fluidThermo_.rho ();
    }
        volScalarField const& 
    dynamic_viscosity () const override
    {
        return fluidThermo_.mu ();
    }

    void initialize () override
    {
        // There is nothing to do
    }

    void update () override
    {
        // There is nothing to do
    }
};

} // namespace geochemistryModels
} // namespace Foam
