#pragma once
#include "geochemistryNone.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

    class 
geochemistryTransportOnly
    : public geochemistryNone
{
    /*
        dictionary 
    coeffDict_;
        dimensionedScalar 
    eps0_;
        volScalarField 
    eps_;
        volScalarField 
    massSourceTerm_;
    */
public:

    TypeName ("geochemistryTransportOnly");

    geochemistryTransportOnly (
          fvMesh const& mesh
        , porousMedia& parent
        , word const& name = "geochemistryTransportOnly"
    );

    ~geochemistryTransportOnly ()
    {}

    void update () override
    {
        // TODO
    }
};

} // End namespace geochemistryModels
} // End namespace Foam
