#include "absolutePermeabilityConst.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedium.H"

    namespace 
Foam
{
    namespace 
absolutePermeabilityModels
{

OPENFOAM_RUNTIME_SELECTOR_ADD(absolutePermeabilityModel, absolutePermeabilityConst)

absolutePermeabilityConst::absolutePermeabilityConst (
      const fvMesh& mesh
    , porousMedium& parent
    , word const& name
)
    : absolutePermeabilityModel { mesh, parent, name }
    , K0_ { "K0", dimLength * dimLength, dict () }
    , K_ {
          IOobject {
              "K"
            , mesh.time ().name ()
            , mesh
            , IOobject::READ_IF_PRESENT
            , IOobject::AUTO_WRITE
          }
        , mesh
        , K0_
        , "zeroGradient"
    }
{}

} // namespace absolutePermeabilityModels
} // namespace Foam
