#pragma once
#include "nonCopyable.H"
#include "mediumBase.H"
#include "hashedWordList.H"

    namespace
Foam
{
    template <class Medium>
    class
mediumList
    : public nonCopyable
{
        PtrList <Medium>
    media_;
        const word
    name_;
    
public:
    mediumList (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , word         const& name
    );

        void
    initialize ()
    {
        forAll (media_, mediumIndex)
        {
            media_[mediumIndex].initialize ();
        }
    }

        template <class Model>
    void
    add_model (word const& name)
    {
        forAll (media_, mediumIndex)
        {
            media_[mediumIndex].template add_model <Medium, Model> (name);
        }
    }
        auto const&
    operator [] (label index) const
    {
        return media_[index];
    }
        auto&
    operator [] (label index)
    {
        return media_[index];
    }
        auto
    size () const
    {
        return media_.size ();
    }
};
} // namespace Foam
