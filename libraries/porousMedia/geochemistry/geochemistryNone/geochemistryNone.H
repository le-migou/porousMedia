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
        volScalarField 
    massSourceTerm_;

public:

    TypeName ("geochemistryNone");

    geochemistryNone (
          fvMesh const& mesh
        , porousMedia& parent
        , word const& name = "geochemistryNone"
    );

    ~geochemistryNone ()
    {}

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
        volScalarField const& 
    massSourceTerm () const override
    {
        return massSourceTerm_;
    }

    void update () override
    {}
};

} // namespace geochemistryModels
} // namespace Foam
