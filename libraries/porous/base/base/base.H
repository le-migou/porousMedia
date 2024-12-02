#pragma once
#include "dictionary.H"
#include "fvMesh.H"
#include "fvMesh.H"
#include "nonCopyable.H"

    namespace
Foam
{
    class porousMedium;

// Base class for media and models
    class
base
    : nonCopyable
{
protected: 
        const fvMesh&
    mesh_;
        const porousMedium&
    porous_medium_;
        const word
    name_;
        const dictionary&
    dict_;
public:
    base (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , word         const& name
        , dictionary   const& dict
    )
        : mesh_          { mesh          }
        , porous_medium_ { porous_medium }
        , name_          { name          }
        , dict_          { dict          }
    {}

        virtual
    ~base () = default;

        const auto& 
    porous_medium () const
    {
        return porous_medium_;
    }
        const auto&
    name () const
    {
        return name_;
    }
        const auto&
    dict () const
    {
        return dict_;
    }
        const auto&
    mesh () const
    {
        return mesh_;
    }

    // Called after all media and model objects are constructed
        virtual void
    initialize () = 0;

};
} // namespace Foam
