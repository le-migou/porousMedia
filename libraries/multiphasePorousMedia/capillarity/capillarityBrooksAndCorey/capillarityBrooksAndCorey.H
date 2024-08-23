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
    Foam::capillarityModels::capillarityBrooksAndCorey

Description
    capillarity class that does no capillarity. It merely provides a porosity.

SourceFiles
    capillarityBrooksAndCorey.C

\*---------------------------------------------------------------------------*/

#ifndef capillarityBrooksAndCorey_H
#define capillarityBrooksAndCorey_H

#include "../capillarityModel.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace capillarityModels
{

/*---------------------------------------------------------------------------*\
                          Class capillarityBrooksAndCorey Declaration
\*---------------------------------------------------------------------------*/

class capillarityBrooksAndCorey
:
    public capillarityModel
{

    // Private Data
    
        //- Model coefficients dictionary
        dictionary coeffDict_;

        //- Model parameter
        List <scalar> pc0_;

        //- Model parameter
        List <scalar> alpha_;

        //- ?
        PtrList <volScalarField> const& Se_;

        //- ?
        PtrList <volScalarField> const& dSedS_;

public:

    //- Runtime type information
    TypeName("capillarityBrooksAndCorey");


    // Constructors

        //- Construct from components
        capillarityBrooksAndCorey(
            fvMesh const& mesh,
            multiphasePorousMedia* porousMedia
        );

        //- Disallow default bitwise copy construction
        capillarityBrooksAndCorey(const capillarityBrooksAndCorey&) = delete;


    //- Destructor
    virtual ~capillarityBrooksAndCorey()
    {}


    // Member Functions

        //- ?
        void correct () override;

    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const capillarityBrooksAndCorey&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace capillarityModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
