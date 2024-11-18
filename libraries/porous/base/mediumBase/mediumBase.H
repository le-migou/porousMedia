#pragma once
#include "base.H"

    namespace
Foam
{
    template <class mediumParent>
    class
mediumBase
    : public base <mediumParent>
{
public:
    mediumBase (
          mediumParent const& parent
        , word const& name
        , fvMesh const& mesh
    )
    : base <mediumParent> { 
          parent
        , name
        , parent.dict ().subDict (name + "Properties") 
        , mesh
      }
    {}
};
} // namespace Foam
