#pragma once
#include "mediumList.H"
#include "mineralMedium.H"
#include "volFieldsFwd.H"

    namespace
Foam
{
    class porousMedium;

    class
mineralMediumList
    : public mediumList <mineralMedium>
{
        volScalarField
    inertVolumeFraction_;
public:
    mineralMediumList (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
    );

        const auto&
    inertVolumeFraction () const
    {
        return inertVolumeFraction_;
    }
};
} // namespace Foam
