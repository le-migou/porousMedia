#include "dispersionConst.H"
#include "addToRunTimeSelectionTable.H"
#include "soluteMedium.H"

    namespace 
Foam
{
    namespace 
dispersionModels
{

OPENFOAM_RUNTIME_SELECTOR_ADD(dispersionModel, dispersionConst)

dispersionConst::dispersionConst (
      const fvMesh& mesh
    , soluteMedium& parent
    , word const& name
)
    : dispersionModel { mesh, parent, name }
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

} // namespace dispersionModels
} // namespace Foam
