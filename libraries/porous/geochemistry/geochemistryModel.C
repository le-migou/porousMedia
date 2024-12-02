#include "geochemistryModel.H"
#include "porousMedium.H"

OPENFOAM_RTS_MODEL_IMPLEMENTATION(geochemistryModel, geochemistry)

Foam::geochemistryModel::geochemistryModel (
      fvMesh       const& mesh
    , porousMedium      & porous_medium
    , word         const& name
) 
    : modelBase { mesh, porous_medium, name }
    , fluidThermo_ { porous_medium.thermo () }
{}

