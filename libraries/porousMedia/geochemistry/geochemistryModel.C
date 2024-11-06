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

#include "geochemistryModel.H"
#include "porousMedia.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(geochemistryModel, 0);
    defineRunTimeSelectionTable(
          geochemistryModel
        , dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::geochemistryModel::geochemistryModel
(
    fvMesh const& mesh,
    porousMedia& parent
) 
:
    fluidThermo_(parent.thermo ())
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::geochemistryModel>
Foam::geochemistryModel::New
(
    fvMesh const& mesh,
    porousMedia& parent
)
{
    const word modelType = parent.dict().lookup("geochemistryModel");

    Info<< "Selecting absolute permeability model " << modelType << endl;

    typename dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(modelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown geochemistryModel type "
            << modelType << nl << nl
            << "Valid geochemistryModel types:" << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<geochemistryModel>
    (
        cstrIter()(
            mesh,
            parent
        )
    );
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

/*
bool Foam::geochemistryModel::read()
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


void Foam::geochemistryModel::correct()
{
    viscosityModel_->correct();
    BasicMomentumTransportModel::correct();
}
*/


// ************************************************************************* //
