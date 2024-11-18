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
porousMedium;

    class 
absolutePermeabilityModel
    : public nonCopyable
    , public modelBase <porousMedium>
{
public:
    TypeName ("absolutePermeability");
    OPENFOAM_RUNTIME_SELECTOR_DECLARATION(absolutePermeabilityModel, porousMedium)

    absolutePermeabilityModel (
          const fvMesh& mesh
        , porousMedium& parent
        , word const& name
    )
        : modelBase { parent, name, mesh }
    {}

        virtual 
    ~absolutePermeabilityModel ()
    {}

    // Absolute permeability
        virtual volTensorField const& 
    K () const = 0;
};
} // namespace Foam
