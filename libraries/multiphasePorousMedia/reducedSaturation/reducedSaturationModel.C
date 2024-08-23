/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2022 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "reducedSaturationModel.H"
#include "multiphasePorousMedia.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(reducedSaturationModel, 0);
    defineRunTimeSelectionTable(
          reducedSaturationModel
        , dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::reducedSaturationModel::reducedSaturationModel
(
    fvMesh const& mesh,
    multiphasePorousMedia* parent
) 
:
    parent_(parent),
    phases_(parent->phases ())
{
    forAll(parent_->phases(), i)
    {
        Se_.append (
            new volScalarField 
            (
                IOobject
                (
                    "Se." + phases_[i].name (),
                    mesh.time().name(),
                    mesh,
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                mesh,
                0.
            )
        );
        dSedS_.append (
            new volScalarField 
            (
                IOobject
                (
                    "dSedS." + phases_[i].name (),
                    mesh.time().name(),
                    mesh,
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                mesh,
                0.
            )
        );
    }
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::reducedSaturationModel>
Foam::reducedSaturationModel::New
(
    fvMesh const& mesh,
    multiphasePorousMedia* parent
)
{
    const word modelType = parent->lookup("reducedSaturationModel");

    Info<< "Selecting reduced saturation model " << modelType << endl;

    typename dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(modelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown reducedSaturationModel type "
            << modelType << nl << nl
            << "Valid reducedSaturationModel types:" << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<reducedSaturationModel>
    (
        cstrIter()(
            mesh,
            parent
        )
    );
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// ************************************************************************* //
