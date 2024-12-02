#include "dimensionSets.H"
#include "mineralMediumList.H"
#include "porousMedium.H"

Foam::mineralMediumList::mineralMediumList (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
)
    : mediumList { mesh, porous_medium, "minerals" }
    , inertVolumeFraction_ {
          IOobject {
              "Ys.inert"
            , mesh.time ().name ()
            , mesh
            , IOobject::READ_IF_PRESENT
            , IOobject::AUTO_WRITE
          }
        , mesh
        , dimensionedScalar (dimless, 0)
      }
{}
