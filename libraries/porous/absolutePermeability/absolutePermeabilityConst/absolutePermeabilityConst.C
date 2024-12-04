#include "absolutePermeabilityConst.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedium.H"

    namespace 
Foam
{
    namespace 
absolutePermeabilityModels
{

OPENFOAM_RTS_MODEL_ADD(absolutePermeabilityModel, absolutePermeabilityConst)

absolutePermeabilityConst::absolutePermeabilityConst (
      fvMesh       const& mesh
    , porousMedium      & porous_medium
    , word         const& name
)
    : absolutePermeabilityModel { mesh, porous_medium, name }
    , initial_permeability_ { "initial_permeability", dimLength * dimLength, dict () }
    , permeability_ {
          IOobject {
              "permeability"
            , mesh.time ().name ()
            , mesh
            , IOobject::READ_IF_PRESENT
            , IOobject::AUTO_WRITE
          }
        , mesh
        , initial_permeability_
        , "zeroGradient"
    }
{}

} // namespace absolutePermeabilityModels
} // namespace Foam
