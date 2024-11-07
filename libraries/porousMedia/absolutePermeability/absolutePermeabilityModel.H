#pragma once
#include "runtimeSelection.H"
#include "nonCopyable.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"

    namespace 
Foam
{
    class 
porousMedia;

    class 
absolutePermeabilityModel
    : public nonCopyable
{
        const porousMedia& 
    parent_;

public:
    TypeName ("absolutePermeability");
    
    OPENFOAM_RUNTIME_SELECTOR_DECLARATION(absolutePermeabilityModel)

    absolutePermeabilityModel (const fvMesh& mesh, porousMedia& parent)
        : parent_ (parent)
    {}

        virtual 
    ~absolutePermeabilityModel ()
    {}

    // Absolute permeability
        virtual volTensorField const& 
    K () const = 0;

};
} // namespace Foam
