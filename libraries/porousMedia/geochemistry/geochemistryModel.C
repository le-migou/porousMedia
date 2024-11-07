#include "geochemistryModel.H"
#include "porousMedia.H"

OPENFOAM_RUNTIME_SELECTOR_IMPLEMENTATION(geochemistryModel)

Foam::geochemistryModel::geochemistryModel (
      fvMesh const& mesh
    , porousMedia& parent
) 
    : parent_ (parent)
    , fluidThermo_ (parent.thermo ())
{}

