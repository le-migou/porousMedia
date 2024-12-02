#include "soluteMediumList.H"
#include "porousMedium.H"

Foam::soluteMediumList::soluteMediumList (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
)
    : mediumList { mesh, porous_medium, "solutes" }
{}
