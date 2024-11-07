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
    Foam::geochemistryModels::geochemistryNone

Description
    Geochemistry class that does no geochemistry. It merely provides a porosity.

SourceFiles
    geochemistryNone.C

\*---------------------------------------------------------------------------*/

#ifndef geochemistryConst_H
#define geochemistryConst_H

#include "../geochemistryModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace geochemistryModels
{

/*---------------------------------------------------------------------------*\
                          Class geochemistryNone Declaration
\*---------------------------------------------------------------------------*/

class geochemistryNone
:
    public geochemistryModel
{

    // Private Data
    
        //- Model coefficients dictionary
        dictionary coeffDict_;

        //- Initial porosity
        dimensionedScalar eps0_;

        //- Porosity
        volScalarField eps_;

        //- Mass source term
        volScalarField massSourceTerm_;

public:

    //- Runtime type information
    TypeName("geochemistryNone");


    // Constructors

        //- Construct from components
        geochemistryNone(
            fvMesh const& mesh,
            porousMedia& parent
        );

        //- Disallow default bitwise copy construction
        geochemistryNone(const geochemistryNone&) = delete;


    //- Destructor
    virtual ~geochemistryNone()
    {}


    // Member Functions

        //- Return the porosity
        volScalarField const& eps() const override;

        //- Return the density of the fluid
        volScalarField const& rho() const override;

        //- Return the viscosity of the fluid
        volScalarField const& mu() const override;

        //- Source term for the flow solver
        volScalarField const& massSourceTerm() const override;

        void update() override
        {}


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const geochemistryNone&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geochemistryModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "geochemistryNone.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
