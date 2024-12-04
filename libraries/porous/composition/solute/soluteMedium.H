#pragma once
#include "fvMesh.H"
#include "mediumBase.H"
#include "volFields.H"
#include "dispersionModel.H"

    namespace
Foam
{
    class porousMedium;

    class
soluteMedium 
    : public mediumBase
{
        volScalarField
    concentration_;

public:

    soluteMedium (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , word         const& name
    );

        volScalarField&
    concentration ()
    {
        return concentration_;
    }
        const volScalarField&
    concentration () const
    {
        return concentration_;
    }

        const auto&
    dispersion () const
    {
        return get_model <dispersionModel> ("dispersion") -> dispersion ();
    }
};
} // namespace Foam
