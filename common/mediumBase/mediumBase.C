#include "mediumBase.H"

    namespace
Foam
{
    template <class mediumParent>
mediumBase<mediumParent>::mediumBase (
      mediumParent const& parent
    , word const& name
)
    : base <mediumParent> { 
            parent
        , name
        , parent.dict ().subDict (name + "Properties") 
        }
{}
} // namespace Foam
