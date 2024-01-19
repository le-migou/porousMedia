
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2013-2023 OpenFOAM Foundation
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
    Foam::absolutePermeabilityModel

Description
    Base class for the absolute permeablity models of a porous medium.

SourceFiles
    absolutePermeabilityModel.C

\*---------------------------------------------------------------------------*/

#ifndef absolutePermeabilityModel_H
#define absolutePermeabilityModel_H

#include "dictionary.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                          Class absolutePermeabilityModel Declaration
\*---------------------------------------------------------------------------*/

class absolutePermeabilityModel
{
public:

    //- Runtime type information
    TypeName("absolutePermeability");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            absolutePermeabilityModel,
            dictionary,
            (
                const fvMesh& mesh,
                const dictionary& dict
            ),
            (
                mesh, 
                dict
            )
        );


    // Constructors

        //- Construct from components
        absolutePermeabilityModel(
            const fvMesh& mesh, 
            const dictionary& dict
        );

        //- Disallow default bitwise copy construction
        absolutePermeabilityModel(const absolutePermeabilityModel&) = delete;


    // Selectors

        //- Return a reference to the selected absolute permeability model
        static autoPtr<absolutePermeabilityModel> New
        (
            const fvMesh& mesh,
            const dictionary& dict
            
        );


    //- Destructor
    virtual ~absolutePermeabilityModel()
    {}


    // Member Functions
        /*
        //- Read model coefficients if they have changed
        virtual bool read() = 0;
        */

        //- Return the absolute permeability
        virtual volTensorField const& K() const = 0;

        /*
        //- Solve the turbulence equations and correct the turbulence viscosity
        virtual void correct() = 0;
        */


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const absolutePermeabilityModel&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "absolutePermeabilityModel.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
