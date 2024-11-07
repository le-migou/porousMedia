#include "geochemistryNone.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedia.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

defineTypeNameAndDebug (geochemistryNone, 0);
addToRunTimeSelectionTable (geochemistryModel, geochemistryNone, dictionary);

geochemistryNone::geochemistryNone (fvMesh const& mesh, porousMedia& parent)
    : geochemistryModel { mesh, parent }
    , coeffDict_ { parent.dict ().subDict (type () + "Coeffs") }
    , eps0_  { "eps0", dimless, coeffDict_ }
    , eps_ {
          IOobject {
              "eps"
            , mesh.time ().name ()
            , mesh
            , IOobject::NO_READ
            , IOobject::NO_WRITE
          }
        , mesh
        , eps0_
      }
    , massSourceTerm_ {
          IOobject {
              "massSourceTerm"
            , mesh.time ().name ()
            , mesh
            , IOobject::NO_READ
            , IOobject::NO_WRITE
          }
        , mesh
        , dimensionedScalar { dimless/dimTime, 0 }
    }
{}

} // namespace geochemistryModels
} // namespace Foam
