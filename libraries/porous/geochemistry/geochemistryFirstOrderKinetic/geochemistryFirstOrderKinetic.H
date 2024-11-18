#pragma once
#include "geochemistryModel.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

    class 
geochemistryFirstOrderKinetic
    : public geochemistryModel
{
public:

    TypeName ("geochemistryFirstOrderKinetic");

    geochemistryFirstOrderKinetic (
          fvMesh const& mesh
        , porousMedium& parent
        , word const& name = "geochemistryFirstOrderKinetic"
    );

    ~geochemistryFirstOrderKinetic ()
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
