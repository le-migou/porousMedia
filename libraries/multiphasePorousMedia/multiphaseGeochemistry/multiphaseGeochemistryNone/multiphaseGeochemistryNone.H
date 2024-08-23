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
    Foam::multiphaseGeochemistryModels::multiphaseGeochemistryNone

Description
    multiphaseGeochemistry class that does no multiphaseGeochemistry. It merely provides a porosity.

SourceFiles
    multiphaseGeochemistryNone.C

\*---------------------------------------------------------------------------*/

#ifndef multiphaseGeochemistryConst_H
#define multiphaseGeochemistryConst_H

#include "../multiphaseGeochemistryModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace multiphaseGeochemistryModels
{

/*---------------------------------------------------------------------------*\
                          Class multiphaseGeochemistryNone Declaration
\*---------------------------------------------------------------------------*/

class multiphaseGeochemistryNone
:
    public multiphaseGeochemistryModel
{

    // Private Data
    
        //- ?
        // This should be const&
        // But compressibleMultiphaseVoFMixture does not have const access to
        // its phases.
        compressibleMultiphaseVoFMixture& mixture_;

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
    TypeName("multiphaseGeochemistryNone");


    // Constructors

        //- Construct from components
        multiphaseGeochemistryNone(
            fvMesh const& mesh,
            multiphasePorousMedia* parent
        );

        //- Disallow default bitwise copy construction
        multiphaseGeochemistryNone(const multiphaseGeochemistryNone&) = delete;


    //- Destructor
    virtual ~multiphaseGeochemistryNone()
    {}


    // Member Functions

        //- Return the porosity
        volScalarField const& eps() const override
        {
            return eps_;
        }

        //- Return the density of the fluid
        volScalarField const& rho() const override
        {
            return mixture_.rho();
        }
        volScalarField const& rho(label phase_index) const override
        {
            return mixture_.phases()[phase_index].thermo().rho();
        }

        //- Return the viscosity of the fluid
        volScalarField const& mu() const override
        {
            return mixture_.nu() * mixture_.rho();
        }
        volScalarField const& mu(label phase_index) const override
        {
            return mixture_.phases()[phase_index].thermo().mu();
        }

        //- Source term for the flow solver
        volScalarField const& massSourceTerm() const override
        {
            return massSourceTerm_;
        }


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const multiphaseGeochemistryNone&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace multiphaseGeochemistryModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "multiphaseGeochemistryNone.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
