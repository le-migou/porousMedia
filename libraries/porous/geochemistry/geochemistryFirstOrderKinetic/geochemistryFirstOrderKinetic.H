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
    porosity_;
        volScalarField 
    old_porosity_;

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
    porosity () const override
    {
        return porosity_;
    }
        volScalarField const& 
    old_porosity () const override
    {
        return old_porosity_;
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

        void 
    initialize () override;

        void 
    update () override;
};

} // namespace geochemistryModels
} // namespace Foam
