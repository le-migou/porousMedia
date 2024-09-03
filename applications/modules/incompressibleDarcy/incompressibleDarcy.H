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
    Foam::solvers::incompressibleDarcy

Description
    Solver module for the incompressible flow in porous media, based on the 
    incompressibleFluid solver.

SourceFiles
    incompressibleDarcy.C

See also
    Foam::solvers::fluidSolver
    Foam::solvers::isothermalFluid

\*---------------------------------------------------------------------------*/

#ifndef incompressibleDarcy_H
#define incompressibleDarcy_H

#include "incompressibleFluid.H"
#include "porousMedia.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace solvers
{

/*---------------------------------------------------------------------------*\
                          Class incompressibleDarcy Declaration
\*---------------------------------------------------------------------------*/

class incompressibleDarcy
:
    public incompressibleFluid
{

    // Private data

        //- The porous medium properties and models
        porousMedia porousMedia_;

        //- The inverse of the permeability tensor
        // FIXME: this is scalar ATM, I don't have a solution for adding an
        // implicit source which is a tensor.
        volScalarField nuInvK_;

public:

    //- Runtime type information
    TypeName("incompressibleDarcy");


    // Constructors

        //- Construct from region mesh
        incompressibleDarcy(fvMesh& mesh);

        //- Disallow default bitwise copy construction
        incompressibleDarcy(const incompressibleDarcy&) = delete;


    //- Destructor
    virtual ~incompressibleDarcy();


    // Member Functions

        //- Construct and optionally solve the momentum equation
        void momentumPredictor() override;

    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const incompressibleDarcy&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace solvers
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
