#include "soluteMedium.H"
#include "porousMedium.H"

Foam::soluteMedium::soluteMedium (
      const fvMesh& mesh
    , porousMedium& parent
    , word const& name
)
    : mediumBase { parent, name }
    , concentration_ { new volScalarField (
            IOobject {
                "C." + name
            , mesh.time ().name ()
            , mesh
            , IOobject::MUST_READ
            , IOobject::AUTO_WRITE
            }
        , mesh
        ) }
{}
