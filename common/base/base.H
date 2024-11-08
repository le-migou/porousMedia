#pragma once
#include "dictionary.H"

namespace
Foam
{
    template <class ModelParent>
    class
base
{
protected: 
        ModelParent&
    parent_;
        word
    name_;
        dictionary const&
    dict_;
public:
    base (
          ModelParent& parent
        , word const& name
        , dictionary const& dict
    )
        : parent_ { parent }
        , name_ { name }
        , dict_ { dict }
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
};
} // namespace Foam
