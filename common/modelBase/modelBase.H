#pragma once
#include "dictionary.H"

namespace
Foam
{
    template <class ModelParent>
    class
modelBase
{
protected: 
        ModelParent&
    parent_;
        word
    name_;
        dictionary 
    dict_;
public:
    modelBase (
          ModelParent& parent
        , word const& name
    )
        : parent_ { parent }
        , name_ { name }
        , dict_ { parent.dict ().subDict (name + "Parameters") }
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
