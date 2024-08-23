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
    Foam::capillarityModel

Description
    Base class for modelling the dissoution, transport and precipitation of 
    dissolved minerals in porous media.

SourceFiles
    capillarityModel.C

\*---------------------------------------------------------------------------*/

#ifndef capillarityModel_H
#define capillarityModel_H

#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"
#include "compressibleVoFphase.H"
#include "UPtrListDictionary.H"



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class multiphasePorousMedia;

/*---------------------------------------------------------------------------*\
                          Class capillarityModel Declaration
\*---------------------------------------------------------------------------*/

class capillarityModel
{
protected:

        //- ?
        multiphasePorousMedia* parent_;

        //- Reference to the phases
        UPtrListDictionary<compressibleVoFphase> const& phases_;

        //- Capillary pressure
        PtrList <volScalarField> pc_;

        //- Derivative w.r.t. saturation
        PtrList <volScalarField> dpcdS_;

public:

    //- Runtime type information
    TypeName("capillarity");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            capillarityModel,
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
        capillarityModel(
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );

        //- Disallow default bitwise copy construction
        capillarityModel(const capillarityModel&) = delete;


    // Selectors

        //- Return a reference to the selected absolute permeability model
        static autoPtr<capillarityModel> New
        (
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );


    //- Destructor
    virtual ~capillarityModel()
    {}


    // Member Functions

        //- Return the capillary pressure
        volScalarField const& pc(label interface_index) const
        {
            return pc_[interface_index];
        }

        //- Return the capillary pressure
        PtrList <volScalarField> const& pc() const
        {
            return pc_;
        }

        //- Return the derivative of capillary pressure
        volScalarField const& dpcdS(label interface_index) const
        {
            return dpcdS_[interface_index];
        }

        //- Return the derivative of capillary pressure
        PtrList <volScalarField> const& dpcdS() const
        {
            return dpcdS_;
        }

        //- ?
        virtual void correct () = 0;


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const capillarityModel&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
