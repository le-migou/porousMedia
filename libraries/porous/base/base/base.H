#pragma once
#include "dictionary.H"
#include "fvMesh.H"
#include "fvMesh.H"

namespace
Foam
{
    template <class ModelParent>
    class
base
{
protected: 
        ModelParent const&
    parent_;
        word
    name_;
        dictionary const&
    dict_;
        fvMesh const&
    mesh_;
public:
    base (
          ModelParent const& parent
        , word const& name
        , dictionary const& dict
        , fvMesh const& mesh
    )
        : parent_ { parent }
        , name_ { name }
        , dict_ { dict }
        , mesh_ { mesh }
    {}

        auto& 
    parent ()
    {
        return parent_;
    }
        const auto& 
    parent () const
    {
        return parent_;
    }
        auto&
    name ()
    {
        return name_;
    }
        const auto&
    name () const
    {
        return name_;
    }
        auto&
    dict ()
    {
        return dict_;
    }
        const auto&
    dict () const
    {
        return dict_;
    }
        auto&
    mesh ()
    {
        return mesh_;
    }
        const auto&
    mesh () const
    {
        return mesh_;
    }
};
} // namespace Foam
