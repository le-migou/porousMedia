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
    , D0_ { "D0", dimLength * dimLength / dimTime, dict () }
    , D_ {
          IOobject {
              "D"
            , mesh.time ().name ()
            , mesh
            , IOobject::READ_IF_PRESENT
            , IOobject::AUTO_WRITE
          }
        , mesh
        , D0_
        , "zeroGradient"
    }
{}

} // namespace surfaceAreaModels
} // namespace Foam
