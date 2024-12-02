#pragma once
#include "../absolutePermeabilityModel.H"
#include "dimensionedTensor.H"
#include "volFields.H"

    namespace 
Foam
{
    namespace 
absolutePermeabilityModels
{
    class 
absolutePermeabilityConst
    : public absolutePermeabilityModel
{
        dimensionedTensor 
    K0_;
        volTensorField 
    K_;

public:
    TypeName ("absolutePermeabilityConst");

    absolutePermeabilityConst (
          fvMesh       const& mesh
        , porousMedium      & porous_medium
        , word         const& name = "absolutePermeabilityConst"
    );

        volTensorField const& 
    K () const override
    {
        return K_;
    }

        void
    initialize () override
    {
        // There is nothing to do
    }
        void
    update () override
    {
        // There is nothing to do
    }
};

} // namespace absolutePermeabilityModels
} // namespace Foam
