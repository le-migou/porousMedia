#pragma once
#include "../surfaceAreaModel.H"
#include "dimensionedScalar.H"
#include "volFields.H"

    namespace 
Foam
{
    namespace 
surfaceAreaModels
{
    class 
surfaceAreaConst
    : public surfaceAreaModel
{
        dimensionedScalar 
    initial_surface_area_;
        volScalarField 
    surface_area_;

public:
    TypeName ("surfaceAreaConst");

    surfaceAreaConst (
          fvMesh        const& mesh
        , porousMedium  const& porous_medium
        , mineralMedium const& mineral_medium
        , word          const& name = "surfaceAreaConst"
    );

        volScalarField const& 
    surface_area () const override
    {
        return surface_area_;
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

} // namespace surfaceAreaModels
} // namespace Foam
