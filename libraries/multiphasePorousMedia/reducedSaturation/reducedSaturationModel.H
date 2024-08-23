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
    Foam::reducedSaturationModel

Description
    Base class for modelling the dissoution, transport and precipitation of 
    dissolved minerals in porous media.

SourceFiles
    reducedSaturationModel.C

\*---------------------------------------------------------------------------*/

#ifndef reducedSaturationModel_H
#define reducedSaturationModel_H

#include "UPtrListDictionary.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"
#include "compressibleVoFphase.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class multiphasePorousMedia;

/*---------------------------------------------------------------------------*\
                          Class reducedSaturationModel Declaration
\*---------------------------------------------------------------------------*/

class reducedSaturationModel
{
protected:

        multiphasePorousMedia* parent_;

        //- Reference to the phases
        UPtrListDictionary<compressibleVoFphase> const& phases_;

        //- ?
        PtrList <volScalarField> Se_;

        //- ?
        PtrList <volScalarField> dSedS_;

public:

    //- Runtime type information
    TypeName("reducedSaturation");


    // Declare run-time constructor selection table

        declareRunTimeSelectionTable
        (
            autoPtr,
            reducedSaturationModel,
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
        reducedSaturationModel(
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );

        //- Disallow default bitwise copy construction
        reducedSaturationModel(const reducedSaturationModel&) = delete;


    // Selectors

        //- Return a reference to the selected absolute permeability model
        static autoPtr<reducedSaturationModel> New
        (
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );


    //- Destructor
    virtual ~reducedSaturationModel()
    {}


    // Member Functions

        //- Return an effective saturation
        volScalarField const& Se(label phase_index) const 
        {
            return Se_[phase_index];
        }

        //- Return the effective saturations
        PtrList <volScalarField> const& Se() const 
        {
            return Se_;
        }

        //- Return the derivative of an effective saturation
        volScalarField const& dSedS(label phase_index) const
        {
            return dSedS_[phase_index];
        }

        //- Return the derivatives of the effective saturations
        PtrList <volScalarField> const& dSedS() const
        {
            return dSedS_;
        }

        //- ?
        virtual void correct () = 0;
        

    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const reducedSaturationModel&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "reducedSaturationModel.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
