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
#include "uniformDimensionedFields.H"
#include "volFieldsFwd.H"
#include "fixedValueFvPatchField.H"
#include "fvcSnGrad.H"

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
    mixture_(new compressibleMultiphaseVoFMixture(mesh)),
    phases_(mixture_->phases ()),
    multiphasePorousMedia_(mesh, *mixture_, Ss_),
    eps_(multiphasePorousMedia_.eps()),
    sourceTerm_
    (
        IOobject
        (
            "sourceTerm",
            runTime.name(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedScalar("", dimless/dimTime, 0)
    ),
    U_
    (
        IOobject
        (
            "U",
            runTime.name(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedVector("U", dimVelocity, vector::zero)
    ),
    dSmax_(runTime.controlDict().lookupOrDefault<scalar>("dSmax",0.)),
    maxDeltaT_
    (
        runTime.controlDict().lookupOrDefault<scalar>("maxDeletaT", great)
    ),
    maxCo_
    (
        runTime.controlDict().lookupOrDefault<scalar>("maxCo", 0.8)
    )
{
    if (phases_.size () != 2)
    {
        FatalErrorInFunction
            << "multiphaseDarcy only works for 2-phases systems at the moment"
            << abort(FatalError);
    }
    forAll(phases_, i)
    {
        if (i == 0)
        {
            Ss_.append (
                new volScalarField 
                (
                    IOobject
                    (
                        "S." + phases_[i].name (),
                        mesh.time().name(),
                        mesh,
                        IOobject::NO_READ,
                        IOobject::AUTO_WRITE
                    ),
                    mesh,
                    0.
                )
            );
        }
        else
        {
            Ss_.append (
                new volScalarField 
                (
                    IOobject
                    (
                        "S." + phases_[i].name (),
                        mesh.time().name(),
                        mesh,
                        IOobject::MUST_READ,
                        IOobject::AUTO_WRITE
                    ),
                    mesh
                )
            );
        }
        Us_.append (
            new volVectorField 
            (
                IOobject
                (
                    "U." + phases_[i].name (),
                    mesh_.time().name(),
                    mesh_,
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                mesh_
            )
        );
        phis_.append (
            new surfaceScalarField
            (
                IOobject
                (
                    "phi." + phases_[i].name (),
                    mesh_.time().name(),
                    mesh_,
                    IOobject::NO_READ,
                    IOobject::AUTO_WRITE
                ),
                Foam::linearInterpolate(Us_[i]) & mesh.Sf()
            )
        );
    }
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::solvers::multiphaseDarcy::~multiphaseDarcy()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

Foam::scalar Foam::solvers::multiphaseDarcy::maxDeltaT() const
{
    scalarField dSdt = 
          mag(-fvc::div(phis_[1]) + sourceTerm_) ().internalField() 
        / multiphasePorousMedia_.eps ().internalField();
    scalar dSdtmax = gMax(dSdt);
    scalar dtForS = dSmax_ / (dSdtmax + SMALL);

    scalar CoNum = 0.0;
    scalar meanCoNuma = 0.0;
    scalar meanCoNumb = 0.0;

    if (mesh.nInternalFaces())
    {
        scalarField sumPhia
        (
            fvc::surfaceSum(mag(phis_[0]))().internalField()
        );
        scalarField sumPhib
        (
            fvc::surfaceSum(mag(phis_[1]))().internalField()
        );

        CoNum = max(
            gMax(sumPhia / mesh.V()) * runTime.deltaTValue() / 2, 
            gMax(sumPhib / mesh.V()) * runTime.deltaTValue() / 2
        );
        meanCoNuma = (gSum(sumPhia)/gSum(mesh.V())) * runTime.deltaTValue() / 2;
        meanCoNumb = (gSum(sumPhib)/gSum(mesh.V())) * runTime.deltaTValue() / 2;
    }
    Info<< "Courant Number mean: " << meanCoNuma << "," << meanCoNumb << " max: " << CoNum << endl;
        scalar
    F = maxCo_ / (CoNum + SMALL);
        scalar
    deltaTFact = min(min(F, 1 + 0.1 * F), 1.2);
    return min(
        dtForS,
        min(
            deltaTFact * runTime.deltaTValue(),
            maxDeltaT_
        )
    );
}

void Foam::solvers::multiphaseDarcy::preSolve()
{
    // Info << "preSolve ()\n";
}

void Foam::solvers::multiphaseDarcy::moveMesh()
{
    // Info << "moveMesh ()\n";
}

void Foam::solvers::multiphaseDarcy::motionCorrector()
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
    Us_[0].correctBoundaryConditions();
    Us_[1].correctBoundaryConditions();
    forAll(mesh.boundary(),patchi)
    {
        if (isA< fixedValueFvPatchField<vector> >(Us_[0].boundaryField()[patchi]))
        {
            phis_[0].boundaryFieldRef()[patchi]
             =
            Us_[0].boundaryField()[patchi] & mesh.Sf().boundaryField()[patchi];
        }
        if (isA< fixedValueFvPatchField<vector> >(Us_[1].boundaryField()[patchi]))
        {
            phis_[1].boundaryFieldRef()[patchi]
             =
            Us_[1].boundaryField()[patchi] & mesh.Sf().boundaryField()[patchi];
        }
    }

    fvScalarMatrix SbEqn
    (
        eps_ * fvm::ddt(Ss_[1]) + fvc::div(phis_[1])
        ==
        - sourceTerm_
    );

    SbEqn.solve();

    Info<< "Saturation b " << " Min(Sb) = " << gMin(Ss_[1]) 
        << " Max(Sb) = " << gMax(Ss_[1]) << endl;


    multiphasePorousMedia_.correct();

    surfaceScalarField phiG("phiG",(multiphasePorousMedia_.Lf() * multiphasePorousMedia_.g()) & mesh.Sf());
    surfaceScalarField phiPc
    (
        "phiPc",
         multiphasePorousMedia_.Mfs(1) * fvc::interpolate(multiphasePorousMedia_.dpcdS(1), "pc") * fvc::snGrad(Ss_[1]) * mesh.magSf()
    );

    fvScalarMatrix pEqn
    (
        fvm::laplacian(-multiphasePorousMedia_.Mf(), multiphasePorousMedia_.p()) + fvc::div(phiG)
        // capillary term
        + fvc::div(phiPc)
        ==
        // event source terms
        - sourceTerm_
    );

    pEqn.solve();

        auto
    phiP = pEqn.flux();

        auto
    phi = phiP+phiG+phiPc;

//    phis_[1] = Fbf*phiP + (Lbf/Lf)*phiG + phiPc;
    phis_[1] = (multiphasePorousMedia_.Mfs(1)/multiphasePorousMedia_.Mf())*phiP + (multiphasePorousMedia_.Lfs(1)/multiphasePorousMedia_.Lf())*phiG + phiPc;
    phis_[0] = phi - phis_[1];

    U_ = fvc::reconstruct(phi);
    U_.correctBoundaryConditions();

    Us_[1] = fvc::reconstruct(phis_[1]);
    Us_[0] = U_ - Us_[1];

    Us_[1].correctBoundaryConditions();
    Us_[0].correctBoundaryConditions();
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
