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
    Foam::relativePermeabilityModel

Description
    Base class for modelling the dissoution, transport and precipitation of 
    dissolved minerals in porous media.

SourceFiles
    relativePermeabilityModel.C

\*---------------------------------------------------------------------------*/

#ifndef relativePermeabilityModel_H
#define relativePermeabilityModel_H

#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"
#include "compressibleMultiphaseVoFMixture.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class multiphasePorousMedia;

/*---------------------------------------------------------------------------*\
                          Class relativePermeabilityModel Declaration
\*---------------------------------------------------------------------------*/

class relativePermeabilityModel
{
protected:

    multiphasePorousMedia* parent_;
        
public:

    //- Runtime type information
    TypeName("relativePermeability");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            relativePermeabilityModel,
            dictionary,
            (
                fvMesh const& mesh, 
                multiphasePorousMedia* parent
            ),
            (
                mesh, 
                parent
            )
        );


    // Constructors

        //- Construct from components
        relativePermeabilityModel(
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );

        //- Disallow default bitwise copy construction
        relativePermeabilityModel(const relativePermeabilityModel&) = delete;


    // Selectors

        //- Return a reference to the selected absolute permeability model
        static autoPtr<relativePermeabilityModel> New
        (
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );


    //- Destructor
    virtual ~relativePermeabilityModel()
    {}


    // Member Functions

        //- Return relative permeabilities according
        virtual volScalarField const& krs(label phase_index) const = 0;

        //- Return the derivatives of relative permeabilities
        virtual volScalarField const& dkrdSs(label phase_index) const = 0;

        //- ?
        virtual surfaceScalarField const& krfs(label phase_index) const = 0;

    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const relativePermeabilityModel&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

#endif

// ************************************************************************* //
