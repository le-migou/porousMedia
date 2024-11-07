#include "absolutePermeabilityConst.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedia.H"

    namespace 
Foam
{
    namespace 
absolutePermeabilityModels
{
    defineTypeNameAndDebug (absolutePermeabilityConst, 0);
    addToRunTimeSelectionTable (
          absolutePermeabilityModel
        , absolutePermeabilityConst
        , dictionary
    );
}
}

    namespace 
Foam
{
    namespace 
absolutePermeabilityModels
{

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
