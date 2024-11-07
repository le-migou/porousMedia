#pragma once
#include "../geochemistryModel.H"

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
        dictionary 
    coeffDict_;
        dimensionedScalar 
    eps0_;
        volScalarField 
    eps_;
        volScalarField 
    massSourceTerm_;

public:

    TypeName ("geochemistryNone");

    geochemistryNone (fvMesh const& mesh, porousMedia& parent);

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

} // End namespace geochemistryModels
} // End namespace Foam
