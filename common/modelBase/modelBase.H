#pragma once
#include "base.H"

namespace
Foam
{
    template <class modelParent>
    class
modelBase
    : public base <modelParent>
{
public:
    modelBase (
          modelParent& parent
        , word const& name
    )
        : base <modelParent> { 
              parent
            , name 
            , parent.dict ().subDict (name + "Parameters") 
          }
    {}
};
} // namespace Foam
