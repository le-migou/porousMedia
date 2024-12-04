#include "dispersionConst.H"
#include "addToRunTimeSelectionTable.H"
#include "soluteMedium.H"

    namespace 
Foam
{
    namespace 
dispersionModels
{

OPENFOAM_RTS_MODEL_ADD(dispersionModel, dispersionConst)

dispersionConst::dispersionConst (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , soluteMedium const& solute_medium
        , word         const& name
)
    : dispersionModel { mesh, porous_medium, solute_medium, name }
    , initial_dispersion_ { "initial_dispersion", dimLength * dimLength / dimTime, dict () }
    , dispersion_ {
          IOobject {
              "dispersion"
            , mesh.time ().name ()
            , mesh
            , IOobject::READ_IF_PRESENT
            , IOobject::AUTO_WRITE
          }
        , mesh
        , initial_dispersion_
        , "zeroGradient"
      }
{}

} // namespace dispersionModels
} // namespace Foam
