#pragma once
#include "fvMesh.H"
#include "mediumBase.H"
#include "nonCopyable.H"
#include "volFields.H"
#include "surfaceAreaModel.H"

    namespace
Foam
{
    class porousMedium;
    class
mineralMedium 
    : public nonCopyable
    , public mediumBase <porousMedium>
{
        volScalarField
    volumeFraction_;
public:

    POROUS_MEDIA_DECLARE_MODEL(surfaceArea)

    mineralMedium (
          const fvMesh& mesh
        , porousMedium& parent
        , word const& name
    );

    ~mineralMedium () = default;

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
        auto&
    surfaceArea ()
    {
        return surfaceAreaModel_-> A ();
    }
        const auto&
    surfaceArea () const
    {
        return surfaceAreaModel_-> A ();
    }
};
} // namespace Foam
