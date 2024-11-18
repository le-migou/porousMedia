#pragma once
#include "nonCopyable.H"
#include "mineralMedium.H"

    namespace
Foam
{
    class porousMedium;
    class
mineralMediumList
    : public nonCopyable
{
        PtrList <mineralMedium>
    data_;
public:
    mineralMediumList (fvMesh const& mesh, porousMedium& parent);

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
