#include "mineralMedium.H"
#include "porousMedium.H"

Foam::mineralMedium::mineralMedium (
      const fvMesh& mesh
    , porousMedium& parent
    , word const& name
)
    : mediumBase { parent, name, mesh }
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
{
    if (name == "inert")
    {
        FatalIOErrorInFunction(dict ())
            << "Mineral name \"inert\" is reserved in dictionary "
            << dict ().name()
            << exit(FatalIOError);
    }
}
