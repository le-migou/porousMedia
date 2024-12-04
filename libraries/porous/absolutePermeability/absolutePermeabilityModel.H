#pragma once
#include "modelBase.H"
#include "runtimeSelection.H"
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
    : public modelBase
{
public:
    TypeName ("absolutePermeability");
    OPENFOAM_RTS_MODEL_DECLARATION(absolutePermeabilityModel)

    absolutePermeabilityModel (
          fvMesh       const& mesh
        , porousMedium      & porous_medium
        , word         const& name
    )
        : modelBase { mesh, porous_medium, name }
    {}

    // Absolute permeability
        virtual volTensorField const& 
    permeability () const = 0;
};
} // namespace Foam
