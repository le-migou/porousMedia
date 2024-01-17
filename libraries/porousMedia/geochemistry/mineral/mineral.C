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

#include "mineral.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(mineral, 0);
    defineRunTimeSelectionTable(
          mineral
        , dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::mineral::mineral
(
      const fvMesh& mesh
    , const dictionary& dict
    , const word& mineralName
) 
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::mineral>
Foam::mineral::New
(
      const fvMesh& mesh
    , const dictionary& dict
    , const word& mineralName
)
{

    const word modelType = dict.lookup("mineral");

    Info<< "Selecting absolute permeability model " << modelType << endl;

    typename dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(modelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown mineral type "
            << modelType << nl << nl
            << "Valid mineral types:" << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<mineral>
    (
        cstrIter()(
              mesh
            , dict
            , mineralName
        )
    );
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

/*
bool Foam::mineral::read()
{
    if (BasicMomentumTransportModel::read())
    {
        RASDict_ <<= this->subDict("RAS");
        RASDict_.lookup("turbulence") >> turbulence_;

        coeffDict_ <<= RASDict_.optionalSubDict(type() + "Coeffs");

        kMin_.readIfPresent(RASDict_);
        epsilonMin_.readIfPresent(RASDict_);
        omegaMin_.readIfPresent(RASDict_);

        return true;
    }
    else
    {
        return false;
    }
    return false;
}


void Foam::mineral::correct()
{
    viscosityModel_->correct();
    BasicMomentumTransportModel::correct();
}
*/


// ************************************************************************* //
