#pragma once
#include "../dispersionModel.H"
#include "dimensionedTensor.H"
#include "volFields.H"

    namespace 
Foam
{
    namespace 
dispersionModels
{
    class 
dispersionConst
    : public dispersionModel
{
        dimensionedTensor 
    initial_dispersion_;
        volTensorField 
    dispersion_;

public:
    TypeName ("dispersionConst");

    dispersionConst (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , soluteMedium const& solute_medium
        , word         const& name = "dispersionConst"
    );

        volTensorField const& 
    dispersion () const override
    {
        return dispersion_;
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

} // namespace dispersionModels
} // namespace Foam
