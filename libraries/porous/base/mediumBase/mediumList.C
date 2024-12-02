#include "mediumList.H"
#include "porousMedium.H"

    template <class Medium>
Foam::mediumList <Medium>::mediumList (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
    , word         const& name

)
    : name_          { name          }
{
        auto&
    dict = porous_medium.dict ();
    Info<< "List of " << name << ":\n";
        auto
    media = dict.lookupOrDefault (name, hashedWordList {});
    forAll (media, index)
    {
            auto const&
        medium_name = media[index];
        Info<< " - " << medium_name << endl;
        media_.append (new Medium { mesh, porous_medium, medium_name });
    }
    Info<< '\n';
}

// Explicit instantiations of constructors.
// The above constructor cannot be put in the header file because it needs a
// complete description of the porousMedium class that is not accessible there
// to avoid circular inclusion. As a consequence, we have to explicitly
// instantiate the ones we sill need here.
    template 
Foam::mediumList <Foam::soluteMedium>::mediumList (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
    , word         const& name
);
    template 
Foam::mediumList <Foam::mineralMedium>::mediumList (
      fvMesh       const& mesh
    , porousMedium const& porous_medium
    , word         const& name
);
