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
mineralMedium;

    class 
surfaceAreaModel
    : public mediumModelBase <mineralMedium>
{
public:
    TypeName ("surfaceArea");
    OPENFOAM_RTS_MEDIUM_MODEL_DECLARATION(surfaceAreaModel, mineralMedium)

    surfaceAreaModel (
          fvMesh        const& mesh
        , porousMedium  const& porous_medium
        , mineralMedium const& mineral_medium
        , word          const& name
    )
        : mediumModelBase { mesh, porous_medium, mineral_medium, name }
    {}

    // Dispersion tensor
        virtual volScalarField const& 
    surface_area () const = 0;
};
} // namespace Foam
