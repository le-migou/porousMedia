#pragma once
#include "base.H"

#define POROUS_MEDIA_DECLARE_MODEL(MODEL)                     \
private:                                                      \
        autoPtr <MODEL##Model>                                \
    MODEL##Model_ { nullptr };                                \
public:                                                       \
    void                                                      \
init_model_##MODEL ()                                         \
{                                                             \
    if (MODEL##Model_.valid ()) return;                       \
    MODEL##Model_ = MODEL##Model::New (mesh (), *this);       \
}

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
