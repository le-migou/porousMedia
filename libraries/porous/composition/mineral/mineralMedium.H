#pragma once
#include "fvMesh.H"
#include "mediumBase.H"
#include "volFields.H"
#include "surfaceAreaModel.H"

    namespace
Foam
{
    class porousMedium;
    class
mineralMedium 
    : public mediumBase
{
        volScalarField
    volumeFraction_;
        dimensionedScalar
    molarVolume_;

public:
    mineralMedium (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , word         const& name
    );

        auto const&
    molarVolume () const
    {
        return molarVolume_;
    }
        auto&
    molarVolume ()
    {
        return molarVolume_;
    }
        auto&
    volumeFraction ()
    {
        return volumeFraction_;
    }
        const auto&
    volumeFraction () const
    {
        return volumeFraction_;
    }
        const auto&
    surface_area () const
    {
        return get_model <surfaceAreaModel> ("surfaceArea") -> surface_area ();
    }
};
} // namespace Foam
