#include "surfaceAreaConst.H"
#include "addToRunTimeSelectionTable.H"
#include "mineralMedium.H"

    namespace 
Foam
{
    namespace 
surfaceAreaModels
{

OPENFOAM_RTS_MODEL_ADD(surfaceAreaModel, surfaceAreaConst)

surfaceAreaConst::surfaceAreaConst (
      fvMesh        const& mesh
    , porousMedium  const& porous_medium
    , mineralMedium const& mineral_medium
    , word          const& name
)
    : surfaceAreaModel { mesh, porous_medium, mineral_medium, name }
    , initial_surface_area_ { "initial_surface_area", dimless / dimLength, dict () }
    , surface_area_ {
          IOobject {
              "surface_area"
            , mesh.time ().name ()
            , mesh
            , IOobject::READ_IF_PRESENT
            , IOobject::AUTO_WRITE
          }
        , mesh
        , initial_surface_area_
        , "zeroGradient"
    }
{}

} // namespace surfaceAreaModels
} // namespace Foam
