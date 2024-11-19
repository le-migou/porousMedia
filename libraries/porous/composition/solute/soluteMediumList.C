#include "soluteMediumList.H"
#include "porousMedium.H"
#include "hashedWordList.H"

Foam::soluteMediumList::soluteMediumList (
      fvMesh const& mesh
    , porousMedium& parent
){
        auto&
    dict = parent.dict ();
        auto
    solutes = dict.lookupOrDefault ("solutes", hashedWordList {});
    forAll (solutes, i)
    {
            auto const&
        solute_name = solutes[i];
            auto
        solute_dict_name = solute_name + "Properties";
            auto
        solute_dict = dict.subDictPtr (solute_dict_name);
        if (solute_dict == nullptr)
        {
            FatalIOErrorInFunction(dict)
                << "keyword " << solute_dict_name << " is undefined in dictionary "
                << dict.name()
                << exit(FatalIOError);

        }
        solutes_.append (new soluteMedium (mesh, parent, solute_name));
    }
}
