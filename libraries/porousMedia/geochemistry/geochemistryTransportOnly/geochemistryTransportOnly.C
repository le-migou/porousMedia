#include "geochemistryTransportOnly.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedia.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

OPENFOAM_RUNTIME_SELECTOR_ADD(geochemistryModel, geochemistryTransportOnly)

geochemistryTransportOnly::geochemistryTransportOnly (
      fvMesh const& mesh
    , porousMedia& parent
    , word const& name
)
    : geochemistryNone { mesh, parent, name }
{}

} // namespace geochemistryModels
} // namespace Foam
