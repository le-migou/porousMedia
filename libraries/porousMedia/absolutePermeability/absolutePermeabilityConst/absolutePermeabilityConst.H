/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2023 OpenFOAM Foundation
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
    Foam::absolutePermeabilityModels::absolutePermeabilityConst

Description
    TODO

SourceFiles
    absolutePermeabilityConst.C

\*---------------------------------------------------------------------------*/

#ifndef absolutePermeabilityConst_H
#define absolutePermeabilityConst_H

#include "../absolutePermeabilityModel.H"
#include "dimensionedTensor.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace absolutePermeabilityModels
{

/*---------------------------------------------------------------------------*\
                          Class absolutePermeabilityConst Declaration
\*---------------------------------------------------------------------------*/

class absolutePermeabilityConst
:
    public absolutePermeabilityModel
{

    // Private Data
    
    //- Model coefficients dictionary
    dictionary coeffDict_;

    //- Model parameter
    dimensionedTensor K0_;

    //- Absolute permeability
    volTensorField K_;


public:

    //- Runtime type information
    TypeName("absolutePermeabilityConst");


    // Constructors

        //- Construct from components
        absolutePermeabilityConst(
            const fvMesh& mesh,
            const dictionary& dict
        );

        //- Disallow default bitwise copy construction
        absolutePermeabilityConst(const absolutePermeabilityConst&) = delete;


    //- Destructor
    virtual ~absolutePermeabilityConst()
    {}


    // Member Functions

        //- absolute permeability
        volTensorField const& K() const;

        /*
        //- Return the absolute permeability for patch
        virtual tmp<scalarField> nu(const label patchi) const
        {
            return nu_.boundaryField()[patchi];
        }
        */


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const absolutePermeabilityConst&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace absolutePermeabilityModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "absolutePermeabilityConst.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
