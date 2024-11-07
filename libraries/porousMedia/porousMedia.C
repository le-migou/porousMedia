#include "porousMedia.H"
#include "fvMesh.H"

    namespace 
Foam
{
    defineTypeNameAndDebug (porousMedia, 0);
}

Foam::porousMedia::porousMedia (const fvMesh& mesh)
    : dict_ { IOobject {
          "porousProperties"
        , mesh.time ().constant ()
        , mesh
        , IOobject::MUST_READ_IF_MODIFIED
        , IOobject::NO_WRITE
        , true
      }}
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
    , solutes_ { dict_.lookupOrDefault ("solutes", speciesTable {}) }
{
    forAll (solutes_, i)
    {
        soluteConcentrations_.append (new volScalarField (
              IOobject {
                "C." + solutes_[i]
                , dict_.time ().name ()
                , mesh
                , IOobject::MUST_READ
                , IOobject::AUTO_WRITE
              }
            , mesh
        ));
    }
}
