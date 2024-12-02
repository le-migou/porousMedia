#pragma once
#include "base.H"

namespace
Foam
{
    class
modelBase
    : public base
{
public:
    modelBase (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , word         const& name
        , dictionary   const& dict
    );

    modelBase (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , word         const& name
    );

    // Called after a new velocity field has been calculated
        virtual void
    update () = 0;
};

    template <class Medium>
    class
mediumModelBase
    : public modelBase
{
        const Medium&
    medium_;

public:
    // The name argument must be last as it will get a default value in derived
    // classes
    mediumModelBase (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , Medium       const& medium
        , word         const& name
    )
    : modelBase { 
          mesh
        , porous_medium
        , name 
        , medium.dict ()
      }
    , medium_ { medium }
{}

        const auto&
    medium () const
    {
        return medium_;
    }
};

} // namespace Foam
