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

#include "capillarityModel.H"
#include "multiphasePorousMedia.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(capillarityModel, 0);
    defineRunTimeSelectionTable(
          capillarityModel
        , dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::capillarityModel::capillarityModel
(
    fvMesh const& mesh,
    multiphasePorousMedia* parent
) 
:
    parent_(parent),
    phases_(parent->phases())
{
    // FIXME: update for more than 2 phases.
    for (int i = 1; i < phases_.size(); ++i)
    {
        word interface_name = phases_[0].name () + "." + phases_[i].name ();
        pc_.append (
            new volScalarField 
            (
                IOobject
                (
                    "pc." + interface_name,
                    mesh.time().name(),
                    mesh,
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                mesh,
                0.
            )
        );
        dpcdS_.append (
            new volScalarField 
            (
                IOobject
                (
                    "dpcdS." + interface_name,
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

Foam::autoPtr<Foam::capillarityModel>
Foam::capillarityModel::New
(
    fvMesh const& mesh,
    multiphasePorousMedia* parent
)
{
    const word modelType = parent->lookup("capillarityModel");

    Info<< "Selecting capillarity model " << modelType << endl;

    typename dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(modelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown capillarityModel type "
            << modelType << nl << nl
            << "Valid capillarityModel types:" << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<capillarityModel>
    (
        cstrIter()(
            mesh,
            parent
        )
    );
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// ************************************************************************* //
