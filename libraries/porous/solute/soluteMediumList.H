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
    data_;
public:
    soluteMediumList (fvMesh const& mesh, porousMedium& parent);

        auto const&
    operator [] (label index) const
    {
        return data_[index];
    }
        auto&
    operator [] (label index)
    {
        return data_[index];
    }
        auto
    size () const
    {
        return data_.size ();
    }
};
} // namespace Foam
