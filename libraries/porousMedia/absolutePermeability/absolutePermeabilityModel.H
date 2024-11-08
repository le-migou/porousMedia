#pragma once
#include "modelBase.H"
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
    , public modelBase <porousMedia>
{
public:
    TypeName ("absolutePermeability");
    OPENFOAM_RUNTIME_SELECTOR_DECLARATION(absolutePermeabilityModel)

    absolutePermeabilityModel (
          const fvMesh& mesh
        , porousMedia& parent
        , word const& name
    )
        : modelBase { parent, name }
    {}

        virtual 
    ~absolutePermeabilityModel ()
    {}

    // Absolute permeability
        virtual volTensorField const& 
    K () const = 0;
};
} // namespace Foam
