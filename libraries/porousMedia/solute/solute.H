#pragma once
#include "mediumBase.H"
#include "porousMedia.H"
#include "volFieldsFwd.H"

    namespace
Foam
{
    class
solute 
    : public nonCopyable
    , public mediumBase <porousMedia>
{
        autoPtr <volScalarField>
    concentration_;
public:
    solute (
          const fvMesh& mesh
        , porousMedia& parent
        , word const& name
    )
        : mediumBase { parent, name }
        , concentration_ { new volScalarField (
              IOobject {
                  "C." + name
                , mesh.time ().name ()
                , mesh
                , IOobject::MUST_READ
                , IOobject::AUTO_WRITE
              }
            , mesh
          ) }
    {}

    ~solute () = default;

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
