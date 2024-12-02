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
        volScalarField 
    eps_;

        void
    update_porosity ();

public:

    TypeName ("geochemistryFirstOrderKinetic");

    geochemistryFirstOrderKinetic (
          fvMesh const& mesh
        , porousMedium& porous_medium
        , word const& name = "geochemistryFirstOrderKinetic"
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

        void 
    initialize () override;

        void 
    update () override;
};

} // namespace geochemistryModels
} // namespace Foam
