#include "porousMedium.H"
#include "fvMesh.H"

    namespace 
Foam
{
    defineTypeNameAndDebug (porousMedium, 0);
}

Foam::porousMedium::porousMedium (
      const fvMesh& mesh
    , solvers::isothermalFluid const& solver
)
    : solver_ { solver }
    , dict_ { IOobject {
          "porousProperties"
        , mesh.time ().constant ()
        , mesh
        , IOobject::MUST_READ_IF_MODIFIED
        , IOobject::NO_WRITE
        , true
      }}
    , soluteList_ { mesh, *this }
    , fluidThermo_ { fluidThermo::New (mesh) }
    , geochemistryModel_ { geochemistryModel::New (mesh, *this) }
    , absolutePermeabilityModel_ { absolutePermeabilityModel::New (mesh, *this) }
    , g_ { IOobject {
          "g"
        , dict_.time ().constant ()
        , mesh
        , IOobject::MUST_READ
        , IOobject::NO_WRITE
      }}
{}
