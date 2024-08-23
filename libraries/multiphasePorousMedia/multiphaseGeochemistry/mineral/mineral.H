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
    Foam::mineral

Description
    TODO

SourceFiles
    mineral.C

\*---------------------------------------------------------------------------*/

#ifndef mineral_H
#define mineral_H

#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                          Class mineral Declaration
\*---------------------------------------------------------------------------*/

class mineral
{
public:

    //- Runtime type information
    TypeName("mineral");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            mineral,
            dictionary,
            (
                  const fvMesh& mesh
                , const dictionary& dict
                , const word& mineralName
            
            ),
            (
                  mesh
                , dict
                , mineralName
            )
        );


    // Constructors

        //- Construct from components
        mineral(
              const fvMesh& mesh
            , const dictionary& dict
            , const word& mineralName = word::null
        );

        //- Disallow default bitwise copy construction
        mineral(const mineral&) = delete;


    // Selectors

        //- Return a reference to the selected absolute permeability model
        static autoPtr<mineral> New
        (
              const fvMesh& mesh
            , const dictionary& dict
            , const word& mineralName 
            
        );


    //- Destructor
    virtual ~mineral()
    {}


    // Member Functions
        /*
        //- Read model coefficients if they have changed
        virtual bool read() = 0;
        */

    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const mineral&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "mineral.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
