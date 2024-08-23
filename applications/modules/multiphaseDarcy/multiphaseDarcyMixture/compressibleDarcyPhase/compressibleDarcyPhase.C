/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2023 OpenFOAM Foundation
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

#include "compressibleDarcyPhase.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::compressibleDarcyPhase::compressibleDarcyPhase
(
    const word& name,
    const fvMesh& mesh,
    const volScalarField& T
)
:
    compressibleVoFphase(name, mesh, T),
    U_
    (
        IOobject
        (
            "U",
            mesh.time().name(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector(dimVelocity, vector::zero)
    )
    /*
    thermo_(nullptr),
    Alpha_
    (
        IOobject
        (
            IOobject::groupName("Alpha", name),
            mesh.time().name(),
            mesh
        ),
        mesh,
        dimensionedScalar(dimless, 0)
    ),
    dgdt_
    (
        IOobject
        (
            IOobject::groupName("dgdt", name),
            mesh.time().name(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar(dimless/dimTime, 0)
    )
    */
{
    /*
    {
        volScalarField Tp(IOobject::groupName("T", name), T);
        Tp.write();
    }

    thermo_ = rhoThermo::New(mesh, name);
    thermo_->validate(name, "e");
    */
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
/*
Foam::autoPtr<Foam::DarcyPhase> Foam::compressibleDarcyPhase::clone() const
{
    NotImplemented;
    return autoPtr<DarcyPhase>(nullptr);
}


void Foam::compressibleDarcyPhase::correct
(
    const volScalarField& p,
    const volScalarField& T
)
{
    thermo_->he() = thermo_->he(p, T);
    thermo_->correct();
}
*/

// ************************************************************************* //
