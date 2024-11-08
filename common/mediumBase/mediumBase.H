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
          mediumParent& parent
        , word const& name
    )
        : base <mediumParent> { 
              parent
            , name
            , parent.dict ().subDict (name + "Properties") 
          }
    {}
};
} // namespace Foam
