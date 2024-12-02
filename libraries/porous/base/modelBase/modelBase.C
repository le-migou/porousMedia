#include "modelBase.H"
#include "porousMedium.H"

Foam::modelBase::modelBase (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
    , word         const& name
    , dictionary   const& base_dict
)
    : base { 
          mesh
        , porous_medium
        , name 
        , base_dict.subDict (name + "Parameters") 
      }
{}
Foam::modelBase::modelBase (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
    , word         const& name
)
    : modelBase { 
          mesh
        , porous_medium
        , name 
        , porous_medium.dict ()
      }
{}
