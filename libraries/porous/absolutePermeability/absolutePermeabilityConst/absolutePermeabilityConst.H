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
    initial_permeability_;
        volTensorField 
    permeability_;

public:
    TypeName ("absolutePermeabilityConst");

    absolutePermeabilityConst (
          fvMesh       const& mesh
        , porousMedium      & porous_medium
        , word         const& name = "absolutePermeabilityConst"
    );

        volTensorField const& 
    permeability () const override
    {
        return permeability_;
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
