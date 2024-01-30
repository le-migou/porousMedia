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

#include "multiphaseDarcy.H"
#include "addToRunTimeSelectionTable.H"

#include "dimensionSets.H"
#include "surfaceInterpolate.H"
#include "fvmLaplacian.H"
#include "fvcReconstruct.H"
#include "volFieldsFwd.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    namespace solvers
    {
        defineTypeNameAndDebug(multiphaseDarcy, 0);
        addToRunTimeSelectionTable(solver, multiphaseDarcy, fvMesh);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::solvers::multiphaseDarcy::multiphaseDarcy(fvMesh& mesh)
: 
    solver(mesh),
    multiphasePorousMedia_(mesh),
    K_(multiphasePorousMedia_.K()),     
    mu_(multiphasePorousMedia_.mu()),   
    rho_(multiphasePorousMedia_.rho()), 
    g_(multiphasePorousMedia_.g()),
    sourceTerm_ (multiphasePorousMedia_.massSourceTerm()),
    U_
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector(dimVelocity, vector::zero)
    )
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::solvers::multiphaseDarcy::~multiphaseDarcy()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Foam::scalar Foam::solvers::multiphaseDarcy::maxDeltaT() const
{
    return 0;
}

void Foam::solvers::multiphaseDarcy::preSolve()
{
    // Info << "preSolve ()\n";
}

void Foam::solvers::multiphaseDarcy::moveMesh()
{
    // Info << "moveMesh ()\n";
}

void Foam::solvers::multiphaseDarcy::prePredictor()
{
    // Info << "prePredictor ()\n";
}

void Foam::solvers::multiphaseDarcy::momentumPredictor()
{
    // Info << "momentumPredictor ()\n";
}

void Foam::solvers::multiphaseDarcy::thermophysicalPredictor()
{
    // Info << "thermophysicalPredictor ()\n";
}

void Foam::solvers::multiphaseDarcy::pressureCorrector()
{
}

void Foam::solvers::multiphaseDarcy::postCorrector()
{
    // Info << "postCorrector ()\n";
}

void Foam::solvers::multiphaseDarcy::postSolve()
{
    // Info << "postSolve ()\n";
}

// ************************************************************************* //
