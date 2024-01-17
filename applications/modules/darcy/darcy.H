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

Class
    isto::foam::solvers::darcy

Description

SourceFiles
    darcy.C

\*---------------------------------------------------------------------------*/

#ifndef darcy_H
#define darcy_H

#include "solver.H"
#include "porousMedia.H"
#include "buoyancy.H"
#include "volFieldsFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace solvers
{

/*---------------------------------------------------------------------------*\
                          Class darcy Declaration
\*---------------------------------------------------------------------------*/

class darcy
:
    public solver
{
    // Private data

        //- The porous media
        porousMedia porousMedia_;

        //- Shortcuts
        volTensorField const& K_;
        volScalarField const& mu_;
        volScalarField const& rho_;
        uniformDimensionedVectorField const& g_;
        volScalarField const& sourceTerm_;

        //- The pressure field
        volScalarField p_;

        //- The velocity field
        volVectorField U_;


    // Kinematic properties

        /*
        //- Velocity field
        volVectorField U_;
        */
        /*
        surfaceTensorField Mf_;
        surfaceScalarField phiG_;
        */
        /*
    surfaceScalarField phiPc;
        */

protected:
public:

    // Public Data

        /*
        //- Reference to the fluid thermophysical properties
        const fluidThermo& thermo;

        //- Reference to the pressure field
        const volScalarField& p;

        //- Reference to the continuity density field
        const volScalarField& rho;

        //- Velocity field
        const volVectorField& U;
        */

    //- Runtime type information
    TypeName("darcy");


    // Constructors

        //- Construct from region mesh and thermophysical properties
        //darcy(fvMesh& mesh, autoPtr<fluidThermo> thermo);

        //- Construct from region mesh
        darcy(fvMesh& mesh);

        //- Disallow default bitwise copy construction
        darcy(const darcy&) = delete;


    //- Destructor
    virtual ~darcy();

    // Member Functions

        //- Return the current maximum time-step for stable solution
        scalar maxDeltaT() const override;

        //- Called at the start of the time-step, before the PIMPLE loop
        void preSolve() override;

        //- Called at the start of the PIMPLE loop to move the mesh
        void moveMesh() override;

        //- Called at the start of the PIMPLE loop
        void prePredictor() override;

        //- Construct and optionally solve the momentum equation
        void momentumPredictor() override;

        //- Construct and solve the thermophysical property equations,
        //  convert to temperature
        //  and update thermophysical and transport properties
        void thermophysicalPredictor() override;

        //- Construct and solve the pressure equation in the PISO loop
        void pressureCorrector() override;

        //- Correct the momentum and thermophysical transport modelling
        void postCorrector() override;

        //- Called after the PIMPLE loop at the end of the time-step
        void postSolve() override;


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const darcy&) = delete;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace solvers
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
