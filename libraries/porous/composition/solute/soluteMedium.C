#include "soluteMedium.H"
#include "porousMedium.H"

Foam::soluteMedium::soluteMedium (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
    , word         const& name
)
    : mediumBase { mesh, porous_medium, name }
    , concentration_ { 
            IOobject {
              "C." + name
            , mesh.time ().name ()
            , mesh
            , IOobject::MUST_READ
            , IOobject::AUTO_WRITE
            }
        , mesh
      }
{}
