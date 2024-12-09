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
    , mesh_                      { mesh }
    , soluteList_                { mesh, *this }
    , mineralList_               { mesh, *this }
    , soluteMineralPairList_     { mesh, *this }
    , fluidThermo_               { fluidThermo::New (mesh) }
    , geochemistryModel_         { geochemistryModel::New (mesh, *this) }
    , absolutePermeabilityModel_ { absolutePermeabilityModel::New (mesh, *this) }
    , g_ { IOobject {
          "g"
        , dict_.time ().constant ()
        , mesh
        , IOobject::MUST_READ
        , IOobject::NO_WRITE
      }}
{
    soluteList_.initialize ();
    mineralList_.initialize ();
    soluteMineralPairList_.initialize ();
    geochemistryModel_->initialize ();
    absolutePermeabilityModel_->initialize ();
}

    void
Foam::porousMedium::update ()
{
    geochemistryModel_->update ();
    absolutePermeabilityModel_->update ();
    // TODO: update thermo
}
