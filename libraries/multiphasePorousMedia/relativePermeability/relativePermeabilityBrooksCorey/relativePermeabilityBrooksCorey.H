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
    Foam::relativePermeabilityModels::relativePermeabilityBrooksCorey

Description
    relativePermeability class that does no relativePermeability. It merely provides a porosity.

SourceFiles
    relativePermeabilityBrooksCorey.C

\*---------------------------------------------------------------------------*/

#ifndef relativePermeabilityBrooksCorey_H
#define relativePermeabilityBrooksCorey_H

#include "../relativePermeabilityModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace relativePermeabilityModels
{

/*---------------------------------------------------------------------------*\
                Class relativePermeabilityBrooksCorey Declaration
\*---------------------------------------------------------------------------*/

class relativePermeabilityBrooksCorey
:
    public relativePermeabilityModel
{

    // Private Data
    
        //- Model coefficients dictionary
        dictionary coeffDict_;

public:

    //- Runtime type information
    TypeName("relativePermeabilityBrooksCorey");


    // Constructors

        //- Construct from components
        relativePermeabilityBrooksCorey(
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );

        //- Disallow default bitwise copy construction
        relativePermeabilityBrooksCorey(const relativePermeabilityBrooksCorey&) = delete;


    //- Destructor
    virtual ~relativePermeabilityBrooksCorey()
    {}


    // Member Functions

        //- Return relative permeabilities according
        volScalarField const& krs(label phase_index) const override;

        //- Return the derivatives of relative permeabilities
        volScalarField const& dkrdSs(label phase_index) const override;

        //- ?
        surfaceScalarField const& krfs(label phase_index) const override;


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const relativePermeabilityBrooksCorey&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace relativePermeabilityModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "relativePermeabilityBrooksCorey.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
