#include "surfaceAreaConst.H"
#include "addToRunTimeSelectionTable.H"
#include "mineralMedium.H"

    namespace 
Foam
{
    namespace 
surfaceAreaModels
{

OPENFOAM_RUNTIME_SELECTOR_ADD(surfaceAreaModel, surfaceAreaConst)

surfaceAreaConst::surfaceAreaConst (
      const fvMesh& mesh
    , mineralMedium& parent
    , word const& name
)
    : surfaceAreaModel { mesh, parent, name }
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
