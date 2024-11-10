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
soluteMedium 
    : public nonCopyable
    , public mediumBase <porousMedium>
{
        autoPtr <volScalarField>
    concentration_;
public:
    soluteMedium (
          const fvMesh& mesh
        , porousMedium& parent
        , word const& name
    );

    ~soluteMedium () = default;

        volScalarField&
    concentration ()
    {
        return concentration_();
    }

        const volScalarField&
    concentration () const
    {
        return concentration_;
    }
};
} // namespace Foam
