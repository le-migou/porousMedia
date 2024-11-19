#pragma once
#include "nonCopyable.H"
#include "mineralMedium.H"
#include "volFieldsFwd.H"

    namespace
Foam
{
    class porousMedium;
    class
mineralMediumList
    : public nonCopyable
{
        PtrList <mineralMedium>
    minerals_;
        volScalarField
    inertVolumeFraction_;
public:
    mineralMediumList (fvMesh const& mesh, porousMedium& parent);

        auto const&
    operator [] (label index) const
    {
        return minerals_[index];
    }
        auto&
    operator [] (label index)
    {
        return minerals_[index];
    }
        auto
    size () const
    {
        return minerals_.size ();
    }
        const auto&
    inertVolumeFraction () const
    {
        return inertVolumeFraction_;
    }
};
} // namespace Foam
