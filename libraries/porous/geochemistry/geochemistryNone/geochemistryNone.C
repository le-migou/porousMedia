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
    , initial_porosity_  { "initial_porosity", dimless, dict () }
    , porosity_ {
          IOobject {
              "porosity"
            , mesh.time ().name ()
            , mesh
            , IOobject::NO_READ
            , IOobject::NO_WRITE
          }
        , mesh
        , initial_porosity_
      }
{}

} // namespace geochemistryModels
} // namespace Foam
