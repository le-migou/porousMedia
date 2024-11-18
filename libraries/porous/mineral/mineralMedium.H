#pragma once
#include "fvMesh.H"
#include "mediumBase.H"
#include "nonCopyable.H"
#include "volFields.H"

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
    mineralMedium (
          const fvMesh& mesh
        , porousMedium& parent
        , word const& name
    );

    ~mineralMedium () = default;

        volScalarField&
    volumeFraction ()
    {
        return volumeFraction_;
    }

        const volScalarField&
    volumeFraction () const
    {
        return volumeFraction_;
    }
};
} // namespace Foam
