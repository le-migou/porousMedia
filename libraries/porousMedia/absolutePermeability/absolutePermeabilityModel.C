#include "absolutePermeabilityModel.H"
#include "porousMedia.H"

namespace Foam
{
    defineTypeNameAndDebug (absolutePermeabilityModel, 0);
    defineRunTimeSelectionTable (absolutePermeabilityModel , dictionary);
}

    Foam::autoPtr<Foam::absolutePermeabilityModel>
Foam::absolutePermeabilityModel::New (const fvMesh& mesh, porousMedia& parent)
{

    const word modelType = parent.dict ().lookup ("absolutePermeabilityModel");

    Info<< "Selecting absolute permeability model " << modelType << endl;

    typename dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find (modelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end ())
    {
        FatalErrorInFunction
            << "Unknown absolutePermeabilityModel type "
            << modelType << nl << nl
            << "Valid absolutePermeabilityModel types:" << endl
            << dictionaryConstructorTablePtr_->sortedToc ()
            << exit (FatalError);
    }

    return autoPtr<absolutePermeabilityModel>
    (
        cstrIter ()(
            mesh, 
            parent
        )
    );
}
