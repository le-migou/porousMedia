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
    eps0_;
        volScalarField 
    eps_;

public:

    TypeName ("geochemistryNone");

    geochemistryNone (
          fvMesh       const& mesh
        , porousMedium      & porous_media
        , word         const& name = "geochemistryNone"
    );

        volScalarField const& 
    eps () const override
    {
        return eps_;
    }
        volScalarField const& 
    rho () const override
    {
        return fluidThermo_.rho ();
    }
        volScalarField const& 
    mu () const override
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
