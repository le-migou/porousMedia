#include "geochemistryModel.H"
#include "porousMedia.H"

    namespace 
Foam
{
    defineTypeNameAndDebug (geochemistryModel, 0);
    defineRunTimeSelectionTable (geochemistryModel , dictionary);

geochemistryModel::geochemistryModel ( fvMesh const& mesh, porousMedia& parent) 
    : parent_ (parent)
    , fluidThermo_ (parent.thermo ())
{}

    autoPtr<Foam::geochemistryModel>
geochemistryModel::New (fvMesh const& mesh, porousMedia& parent)
{
    const word modelType = parent.dict ().lookup ("geochemistryModel");

    Info<< "Selecting absolute permeability model " << modelType << endl;

    typename dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find (modelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end ())
    {
        FatalErrorInFunction
            << "Unknown geochemistryModel type "
            << modelType << nl << nl
            << "Valid geochemistryModel types:" << endl
            << dictionaryConstructorTablePtr_->sortedToc ()
            << exit (FatalError);
    }

    return autoPtr<geochemistryModel>
    (
        cstrIter ()(
            mesh,
            parent
        )
    );
}
} // namespace Foam
