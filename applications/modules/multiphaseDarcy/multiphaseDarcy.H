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
    isto::foam::solvers::multiphaseDarcy

Description
    Solves the multiphaseDarcy law of flow through a porous medium.

SourceFiles
    multiphaseDarcy.C

\*---------------------------------------------------------------------------*/

#ifndef multiphaseDarcy_H
#define multiphaseDarcy_H

#include "solver.H"
#include "multiphasePorousMedia.H"
#include "volFieldsFwd.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace solvers
{

/*---------------------------------------------------------------------------*\
                          Class multiphaseDarcy Declaration
\*---------------------------------------------------------------------------*/

class multiphaseDarcy
:
    public solver
{
    // Private data

        //- The compressible two-phase mixture
        autoPtr <compressibleMultiphaseVoFMixture> mixture_;

        //- Reference to the phases
        UPtrListDictionary<compressibleVoFphase>& phases_;
    
        //- The porous medium properties and models
        multiphasePorousMedia multiphasePorousMedia_;
        const volScalarField& eps_;


        PtrList<volScalarField> Ss_;
        PtrList<volVectorField> Us_;
        PtrList<surfaceScalarField> phis_;

        volScalarField sourceTerm_;
        volVectorField U_;

        scalar dSmax_;
        scalar maxDeltaT_;
        scalar maxCo_;

public:

    // Public Data

    //- Runtime type information
    TypeName("multiphaseDarcy");


    // Constructors

        //- Construct from region mesh
        multiphaseDarcy(fvMesh& mesh);

        //- Disallow default bitwise copy construction
        multiphaseDarcy(const multiphaseDarcy&) = delete;


    //- Destructor
    virtual ~multiphaseDarcy();

    // Member Functions

        //- Return the current maximum time-step for stable solution
        scalar maxDeltaT() const override;

        //- Called at the start of the time-step, before the PIMPLE loop
        void preSolve() override;

        //- Called at the start of the PIMPLE loop to move the mesh
        void moveMesh() override;

        //- Corrections that follow mesh motion
        void motionCorrector() override;

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
        void operator=(const multiphaseDarcy&) = delete;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace solvers
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
