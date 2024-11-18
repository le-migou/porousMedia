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
          modelParent const& parent
        , word const& name
        , fvMesh const& mesh
    )
        : base <modelParent> { 
              parent
            , name 
            , parent.dict ().subDict (name + "Parameters") 
            , mesh
          }
    {}
};
} // namespace Foam
