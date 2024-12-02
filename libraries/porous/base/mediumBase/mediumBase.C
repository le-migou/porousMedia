#include "mediumBase.H"
#include "porousMedium.H"

Foam::mediumBase::mediumBase(
      fvMesh       const& mesh
    , porousMedium const& porous_medium
    , word         const& name
)
    : base { 
          mesh
        , porous_medium
        , name
        , porous_medium.dict ().subDict (name + "Properties") 
      }
{}
