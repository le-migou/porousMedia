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

#include "porousMedia.H"
#include "fvMesh.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(porousMedia, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::porousMedia::porousMedia
(
    const fvMesh& mesh
)
:
    dict_(IOobject(
        "porousProperties",
        mesh.time().constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE,
        true
    )),
    fluidThermo_(fluidThermo::New(mesh)),
    geochemistryModel_(geochemistryModel::New(mesh, *this)),
    absolutePermeabilityModel_(absolutePermeabilityModel::New(mesh, *this)),
    g_
    (
        IOobject(
            "g",
            dict_.time().constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    ),
    solutes_(dict_.lookupOrDefault("solutes", speciesTable()))
{
    forAll(solutes_, i)
    {
        Info<< solutes_[i] << endl;
        soluteConcentrations_.append
        (
            new volScalarField
            (
                IOobject
                (
                    "C." + solutes_[i],
                    dict_.time().name(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                mesh
            )
        );
    }
}



// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //
/*
bool Foam::porousMedia::read()
{
    return regIOobject::read();
}
*/


// ************************************************************************* //
