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
    , A0_ { "A0", dimless / dimLength, dict () }
    , A_ {
          IOobject {
              "A"
            , mesh.time ().name ()
            , mesh
            , IOobject::READ_IF_PRESENT
            , IOobject::AUTO_WRITE
          }
        , mesh
        , A0_
        , "zeroGradient"
    }
{}

} // namespace surfaceAreaModels
} // namespace Foam
