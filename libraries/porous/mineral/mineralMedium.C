#include "mineralMedium.H"
#include "porousMedium.H"

Foam::mineralMedium::mineralMedium (
      const fvMesh& mesh
    , porousMedium& parent
    , word const& name
)
    : mediumBase { parent, name }
    , volumeFraction_ { 
            IOobject {
              "Ys." + name
            , mesh.time ().name ()
            , mesh
            , IOobject::MUST_READ
            , IOobject::AUTO_WRITE
            }
        , mesh
      }
{}
