#include "geochemistryNone.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedium.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

OPENFOAM_RTS_MODEL_ADD(geochemistryModel, geochemistryNone)

geochemistryNone::geochemistryNone (
      fvMesh       const& mesh
    , porousMedium      & porous_media
    , word         const& name
)
    : geochemistryModel { mesh, porous_media, name }
    , eps0_  { "eps0", dimless, dict () }
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
    /*
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
        */
{}

} // namespace geochemistryModels
} // namespace Foam
