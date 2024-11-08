#include "geochemistryModel.H"
#include "porousMedia.H"

OPENFOAM_RUNTIME_SELECTOR_IMPLEMENTATION(geochemistryModel, geochemistry)

Foam::geochemistryModel::geochemistryModel (
      fvMesh const& mesh
    , porousMedia& parent
    , word const& name
) 
    : modelBase { parent, name }
    , fluidThermo_ { parent.thermo () }
{}

