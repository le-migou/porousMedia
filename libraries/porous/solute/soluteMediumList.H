#pragma once
#include "nonCopyable.H"
#include "soluteMedium.H"

    namespace
Foam
{
    class porousMedium;
    class
soluteMediumList
    : public nonCopyable
{
        PtrList <soluteMedium>
    solutes_;
public:
    soluteMediumList (fvMesh const& mesh, porousMedium& parent);

        auto const&
    operator [] (label index) const
    {
        return solutes_[index];
    }
        auto&
    operator [] (label index)
    {
        return solutes_[index];
    }
        auto
    size () const
    {
        return solutes_.size ();
    }
};
} // namespace Foam
