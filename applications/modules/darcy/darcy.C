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

#include "darcy.H"
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
        defineTypeNameAndDebug(darcy, 0);
        addToRunTimeSelectionTable(solver, darcy, fvMesh);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::solvers::darcy::darcy(fvMesh& mesh)
: 
    solver(mesh),
    porousMedia_(mesh),
    p_(porousMedia_.p()),
    K_(porousMedia_.K()),     
    mu_(porousMedia_.mu()),   
    rho_(porousMedia_.rho()), 
    g_(porousMedia_.g()),
    sourceTerm_ (porousMedia_.massSourceTerm()),
    U_
    (
        IOobject
        (
            "U",
            runTime.name(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector(dimVelocity, vector::zero)
    )
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::solvers::darcy::~darcy()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Foam::scalar Foam::solvers::darcy::maxDeltaT() const
{
    return 0;
}

void Foam::solvers::darcy::preSolve()
{
    // Info << "preSolve ()\n";
}

void Foam::solvers::darcy::moveMesh()
{
    // Info << "moveMesh ()\n";
}

void Foam::solvers::darcy::motionCorrector()
{
    // Info << "moveMesh ()\n";
}

void Foam::solvers::darcy::prePredictor()
{
    // Info << "prePredictor ()\n";
}

void Foam::solvers::darcy::momentumPredictor()
{
    // Info << "momentumPredictor ()\n";
}

void Foam::solvers::darcy::thermophysicalPredictor()
{
    // Info << "thermophysicalPredictor ()\n";
}

void Foam::solvers::darcy::pressureCorrector()
{
    surfaceTensorField Mf = fvc::interpolate(
        porousMedia_.K() / porousMedia_.mu()
    );
    surfaceScalarField phiG = ((fvc::interpolate(rho_) * Mf) & g_) & mesh.Sf();
    fvScalarMatrix pEqn
    (
        fvm::laplacian(Mf, p_) + fvc::div(phiG) - sourceTerm_
    );
    pEqn.solve();
    surfaceScalarField phi = pEqn.flux() + phiG;
    U_ = fvc::reconstruct(phi);
    U_.correctBoundaryConditions();
}

void Foam::solvers::darcy::postCorrector()
{
    // Info << "postCorrector ()\n";
}

void Foam::solvers::darcy::postSolve()
{
    // Info << "postSolve ()\n";
}

// ************************************************************************* //
