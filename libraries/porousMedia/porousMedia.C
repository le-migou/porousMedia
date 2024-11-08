#include "porousMedia.H"
#include "fvMesh.H"
#include "hashedWordList.H"

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
{
        auto
    solutes = dict_.lookupOrDefault ("solutes", hashedWordList {});
    forAll (solutes, i)
    {
            auto const&
        solute_name = solutes[i];
            auto
        solute_dict_name = solute_name + "Properties";
            auto
        solute_dict = dict_.subDictPtr (solute_dict_name);
        if (solute_dict == nullptr)
        {
            FatalIOErrorInFunction(dict_)
                << "keyword " << solute_dict_name << " is undefined in dictionary "
                << dict_.name()
                << exit(FatalIOError);

        }
        solutes_.append (new solute (mesh, *this, solute_name));
    }
}
