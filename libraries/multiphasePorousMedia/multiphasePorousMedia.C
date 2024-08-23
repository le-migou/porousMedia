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
    const fvMesh& mesh,
    compressibleMultiphaseVoFMixture& mixture,
    PtrList<volScalarField> const& Ss
)
:
    IOdictionary(findModelDict(mesh, true)),
    mixture_(mixture),
    phases_(mixture_.phases()),
    // WARNING: these models might have dependencies between them so the order
    // of their construction is relevant.
    multiphaseGeochemistryModel_(multiphaseGeochemistryModel::New(mesh, this)),
    reducedSaturationModel_(reducedSaturationModel::New(mesh, this)),
    capillarityModel_(capillarityModel::New(mesh, this)),
    absolutePermeabilityModel_(absolutePermeabilityModel::New(mesh, this)),
    relativePermeabilityModel_(relativePermeabilityModel::New(mesh, this)),
    g_
    (
        IOobject(
            "g",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    ),
    Ss_(Ss),
    Lf_
    (
        IOobject(
            "Lf",
            mesh.time().name(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        0.
    ),
    Mf_
    (
        IOobject(
            "Mf",
            mesh.time().name(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        0.
    )
{
    forAll(phases_, i)
    {
        Lfs_.append (
            new surfaceScalarField 
            (
                IOobject
                (
                    "Lf." + phases_[i].name (),
                    mesh.time().name(),
                    mesh,
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                mesh,
                0.
            )
        );
        Mfs_.append (
            new surfaceScalarField 
            (
                IOobject
                (
                    "Mf." + phases_[i].name (),
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
    // Ensure name of IOdictionary is typeName
    //rename(IOobject::groupName(multiphasePorousMedia::typeName, group));
}

//- ?
void Foam::multiphasePorousMedia::correct()
{
    
}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

// ************************************************************************* //
