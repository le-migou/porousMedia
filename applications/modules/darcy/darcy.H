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
    Foam::solvers::darcy

Description
    Solver module for the incompressible flow in porous media, based on the 
    incompressibleFluid solver.

SourceFiles
    darcy.C

See also
    Foam::solvers::fluidSolver
    Foam::solvers::isothermalFluid

\*---------------------------------------------------------------------------*/

#ifndef darcy_H
#define darcy_H

#include "fluid.H"
#include "porousMedia.H"

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
    public fluid
{

    // Private data

        //- The porous medium properties and models
        porousMedia porousMedia_;

        //- The inverse of the permeability tensor
        // FIXME: this is scalar ATM, I don't have a solution for adding an
        // implicit source which is a tensor.
        volScalarField muInvK_;

    // Private Member Functions

        //- Calculate and print the continuity errors
        void continuityErrors();

        //- Construct the continuity equation and correct the density
        void correctDensity();

        //- Construct the pressure equation
        //  and correct the pressure and velocity
        void correctPressure();

        //- Construct the buoyant pressure equation
        //  and correct the pressure and velocity
        void correctBuoyantPressure();

protected:

        //- Construct the pressure equation
        //  and correct the pressure and velocity
        //void correctPressure() override;

public:

    //- Runtime type information
    TypeName("darcy");


    // Constructors

        //- Construct from region mesh
        darcy(fvMesh& mesh);

        //- Disallow default bitwise copy construction
        darcy(const darcy&) = delete;


    //- Destructor
    virtual ~darcy();


    // Member Functions

        //- Construct and optionally solve the momentum equation
        void momentumPredictor() override;
    //
        //- Construct and solve the pressure equation in the PISO loop
        void pressureCorrector() override;


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
