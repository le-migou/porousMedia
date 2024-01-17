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

#include "surfaceInterpolate.H"

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

template <class...> struct S;
Foam::solvers::multiphaseDarcy::multiphaseDarcy(fvMesh& mesh, autoPtr <fluidThermo> thermo)
: 
    solver(mesh),
    fluidThermo_(thermo),
    porousMedia_(new porousMedia (mesh)),
    buoyancy_(buoyancy::New(mesh)),
    Mf_
    (
        IOobject
        (
            "Kf",
            runTime.name(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        fvc::interpolate(porousMedia_->K() / fluidThermo_->mu())
    )
/*
    thermoPtr_(thermoPtr),
    thermo_(thermoPtr_()),

    p_(thermo_.p()),

    rho_
    (
        IOobject
        (
            "rho",
            runTime.name(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        thermo_.renameRho()
    ),

    buoyancy_(buoyancy::New(mesh)),

    p_rgh(buoyancy_.valid() ? buoyancy_->p_rgh : p_),

    U_
    (
        IOobject
        (
            "U",
            runTime.name(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    ),

    thermo(thermo_),
    p(p_),
    rho(rho_),
    U(U_)
    */
{
    /*
        auto x = Kf_ / fluidThermo_->mu ();
        S <decltype (x)> s;
    */
}

Foam::solvers::multiphaseDarcy::multiphaseDarcy(fvMesh& mesh)
: 
    multiphaseDarcy(mesh, fluidThermo::New(mesh))
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
    // Info << "pressureCorrector ()\n";
    Mf_ = fvc::interpolate(
        porousMedia_->K() / idThermo_->mu()
    );

    /*
    phiG = ((fvc::interpolate(rho) * Mf) * buoyancy_->g) & mesh.Sf();

    fvScalarMatrix pEqn
    (
        fvm::laplacian(-Mf, p) + fvc::div(phiG) - sourceTerm
    );

    pEqn.solve();

    phi = pEqn.flux() + phiG;

    U = fvc::reconstruct(phi);
    U.correctBoundaryConditions();
    */
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
