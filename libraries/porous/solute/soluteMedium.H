#pragma once
#include "fvMesh.H"
#include "mediumBase.H"
#include "nonCopyable.H"
#include "volFields.H"
#include "dispersionModel.H"

#define POROUS_MEDIA_DECLARE_MODEL(MODEL)                     \
private:                                                      \
        autoPtr <MODEL##Model>                                \
    MODEL##Model_ { nullptr };                                \
public:                                                       \
    void                                                      \
init_model_##MODEL ()                                         \
{                                                             \
    if (MODEL##Model_.valid ()) return;                       \
    MODEL##Model_ = MODEL##Model::New (mesh (), *this);       \
}

    namespace
Foam
{
    class porousMedium;
    class
soluteMedium 
    : public nonCopyable
    , public mediumBase <porousMedium>
{
        volScalarField
    concentration_;
public:

    POROUS_MEDIA_DECLARE_MODEL(dispersion)

    soluteMedium (
          const fvMesh& mesh
        , porousMedium& parent
        , word const& name
    );

    ~soluteMedium () = default;

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
    D () const
    {
        return dispersionModel_->D ();
    }
};
} // namespace Foam
