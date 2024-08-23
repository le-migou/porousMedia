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
    Foam::reducedSaturationModels::reducedSaturationMinMax

Description
    reducedSaturation class that does no reducedSaturation. It merely provides a porosity.

SourceFiles
    reducedSaturationMinMax.C

\*---------------------------------------------------------------------------*/

#ifndef reducedSaturationConst_H
#define reducedSaturationConst_H

#include "../reducedSaturationModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace reducedSaturationModels
{

/*---------------------------------------------------------------------------*\
                          Class reducedSaturationMinMax Declaration
\*---------------------------------------------------------------------------*/

class reducedSaturationMinMax
:
    public reducedSaturationModel
{

    // Private Data
    
        //- Model coefficients dictionary
        dictionary coeffDict_;

        //- ?
        List <scalar> Smin_;

        //- ?
        List <scalar> Smax_;

public:

    //- Runtime type information
    TypeName("reducedSaturationMinMax");


    // Constructors

        //- Construct from components
        reducedSaturationMinMax(
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );

        //- Disallow default bitwise copy construction
        reducedSaturationMinMax(const reducedSaturationMinMax&) = delete;


    //- Destructor
    virtual ~reducedSaturationMinMax()
    {}


    // Member Functions

        virtual void correct () override;

    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const reducedSaturationMinMax&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace reducedSaturationModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
