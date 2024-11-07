#include "absolutePermeabilityConst.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedia.H"

    namespace 
Foam
{
    namespace 
absolutePermeabilityModels
{

OPENFOAM_RUNTIME_SELECTOR_ADD(absolutePermeabilityModel, absolutePermeabilityConst)

absolutePermeabilityConst::absolutePermeabilityConst (
      const fvMesh& mesh
    , porousMedia& parent
)
    : absolutePermeabilityModel { mesh, parent }
    , coeffDict_ { parent.dict ().subDict (type () + "Coeffs") }
    , K0_ { "K0", dimLength * dimLength, coeffDict_ }
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
