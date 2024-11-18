#include "mineralMediumList.H"
#include "porousMedium.H"
#include "hashedWordList.H"

Foam::mineralMediumList::mineralMediumList (
      fvMesh const& mesh
    , porousMedium& parent
){
        auto&
    dict = parent.dict ();
        auto
    minerals = dict.lookupOrDefault ("minerals", hashedWordList {});
    forAll (minerals, i)
    {
            auto const&
        mineral_name = minerals[i];
            auto
        mineral_dict_name = mineral_name + "Properties";
            auto
        mineral_dict = dict.subDictPtr (mineral_dict_name);
        if (mineral_dict == nullptr)
        {
            FatalIOErrorInFunction(dict)
                << "keyword " << mineral_dict_name << " is undefined in dictionary "
                << dict.name()
                << exit(FatalIOError);

        }
        data_.append (new mineralMedium (mesh, parent, mineral_name));
    }
}
