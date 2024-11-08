#include "geochemistryModel.H"
#include "porousMedium.H"

OPENFOAM_RUNTIME_SELECTOR_IMPLEMENTATION(geochemistryModel, porousMedium, geochemistry)

Foam::geochemistryModel::geochemistryModel (
      fvMesh const& mesh
    , porousMedium& parent
    , word const& name
) 
    : modelBase { parent, name }
    , fluidThermo_ { parent.thermo () }
{}

