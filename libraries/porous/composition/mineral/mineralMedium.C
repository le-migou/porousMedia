#include "mineralMedium.H"
#include "porousMedium.H"

Foam::mineralMedium::mineralMedium (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
    , word         const& name
)
    : mediumBase { mesh, porous_medium, name }
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
    , molarVolume_ { "Vm", dimVolume / dimMoles, dict () }
{
    if (name == "inert")
    {
        FatalIOErrorInFunction(dict ())
            << "Mineral name \"inert\" is reserved in dictionary "
            << dict ().name()
            << exit(FatalIOError);
    }
}
