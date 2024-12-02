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
soluteMedium;

    class 
dispersionModel
    : public mediumModelBase <soluteMedium>
{
public:
    TypeName ("dispersion");
    OPENFOAM_RTS_MEDIUM_MODEL_DECLARATION(dispersionModel, soluteMedium)

    dispersionModel (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , soluteMedium const& solute_medium
        , word         const& name
    )
        : mediumModelBase { mesh, porous_medium, solute_medium, name }
    {}

    // Dispersion tensor
        virtual volTensorField const& 
    D () const = 0;
};
} // namespace Foam
