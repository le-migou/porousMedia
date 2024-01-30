/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2022-2023 OpenFOAM Foundation
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

#include "multiphasePorousMedia.H"
#include "fvMesh.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(multiphasePorousMedia, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * //

Foam::IOobject Foam::multiphasePorousMedia::findModelDict
(
    const objectRegistry& obr,
    bool registerObject
)
{
    typeIOobject<IOdictionary> multiphasePorousMediaIO
    (
        "porousProperties",
        obr.time().constant(),
        obr,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE,
        registerObject
    );

    return multiphasePorousMediaIO;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::multiphasePorousMedia::multiphasePorousMedia
(
    const fvMesh& mesh
)
:
    IOdictionary(findModelDict(mesh, true)),
    compressibleMultiphaseVoFMixture_(new compressibleMultiphaseVoFMixture(mesh)),
    compressibleVoFphases_(compressibleMultiphaseVoFMixture_->phases()),
    //geochemistryModel_(geochemistryModel::New(mesh, *this, fluidThermo_)),
    absolutePermeabilityModel_(absolutePermeabilityModel::New(mesh, *this)),
    g_
    (
        IOobject(
            "g",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    )
{
    // Ensure name of IOdictionary is typeName
    //rename(IOobject::groupName(multiphasePorousMedia::typeName, group));
}



// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
/*
bool Foam::multiphasePorousMedia::read()
{
    return regIOobject::read();
}
*/


// ************************************************************************* //
