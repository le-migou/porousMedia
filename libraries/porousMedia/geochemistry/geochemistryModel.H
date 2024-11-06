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
    Foam::geochemistryModel

Description
    Base class for modelling the dissoution, transport and precipitation of 
    dissolved minerals in porous media.

SourceFiles
    geochemistryModel.C

\*---------------------------------------------------------------------------*/

#ifndef geochemistryModel_H
#define geochemistryModel_H

#include "nonCopyable.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"
#include "hashedWordList.H"
#include "mineral.H"
#include "fluidThermo.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class porousMedia;

/*---------------------------------------------------------------------------*\
                          Class geochemistryModel Declaration
\*---------------------------------------------------------------------------*/

class geochemistryModel
    : public nonCopyable
{
protected:

        //- Thermodynamics of the pure fluid
        fluidThermo const& fluidThermo_;

        //- List of mineral names
        hashedWordList mineral_names_;

        //- Minerals
        PtrList<mineral> minerals_;

        //- solid mass fraction of each mineral
        PtrList<volScalarField> Ys_;

public:

    //- Runtime type information
    TypeName("geochemistry");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            geochemistryModel,
            dictionary,
            (
                fvMesh const& mesh, 
                porousMedia& parent
            ),
            (
                mesh, 
                parent
            )
        );


    // Constructors

        //- Construct from components
        geochemistryModel(
            fvMesh const& mesh,
            porousMedia& parent
        );

    // Selectors

        //- Return a reference to the selected absolute permeability model
        static autoPtr<geochemistryModel> New
        (
            fvMesh const& mesh,
            porousMedia& parent
        );


    //- Destructor
    virtual ~geochemistryModel()
    {}


    // Member Functions
        /*
        //- Read model coefficients if they have changed
        virtual bool read() = 0;
        */

        //- Return the porosity
        virtual volScalarField const& eps() const = 0;

        //- Return the density of the fluid
        virtual volScalarField const& rho() const = 0;

        //- Return the viscosity of the fluid
        virtual volScalarField const& mu() const = 0;

        //- Source term for the flow solver
        virtual volScalarField const& massSourceTerm() const = 0;

        /*
        //- Solve the turbulence equations and correct the turbulence viscosity
        virtual void correct() = 0;
        */


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const geochemistryModel&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "geochemistryModel.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
