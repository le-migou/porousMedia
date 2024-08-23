/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2023 OpenFOAM Foundation
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
    Foam::multiphaseDarcyMixture

Description
    Multiphase mixture for Darcy simulations.

SourceFiles
    multiphaseDarcyMixture.C

See also

\*---------------------------------------------------------------------------*/

#ifndef multiphaseDarcyMixture_H
#define multiphaseDarcyMixture_H

#include "compressibleMultiphaseVoFMixture.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class multiphaseDarcyMixture Declaration
\*---------------------------------------------------------------------------*/

class multiphaseDarcyMixture
:
    public compressibleMultiphaseVoFMixture
{
    // Private Data


public:

    TypeName("multiphaseDarcyMixture");


    // Constructors

        //- Construct from fvMesh
        multiphaseDarcyMixture(const fvMesh& mesh);


    //- Destructor
    virtual ~multiphaseDarcyMixture()
    {}


    // Member Functions
/*
        //- Return the phases
        UPtrListDictionary<compressibleDarcyPhase>& phases()
        {
            return phases_;
        }

        //- Return the mixture density
        virtual const volScalarField& rho() const
        {
            return rho_;
        }

        //- Return true if all phases are incompressible
        bool incompressible() const;

        //- Return the kinematic laminar viscosity
        virtual tmp<volScalarField> nu() const;

        //- Return the laminar viscosity for patch
        virtual tmp<scalarField> nu(const label patchi) const;

        //- Return the face-interpolated dynamic laminar viscosity
        tmp<surfaceScalarField> nuf() const;

        //- Return the mixture compressibility/density
        virtual tmp<volScalarField> psiByRho() const;

        //- Correct the thermodynamics of each phase
        virtual void correctThermo();

        //- Return the effective temperature transport coefficient
        //  derived from the phase internal energy equations i.e. <kappa/Cv>
        virtual tmp<volScalarField> alphaEff
        (
            const volScalarField& nut
        ) const;

        //- Return the phase-averaged reciprocal Cv
        tmp<volScalarField> rCv() const;

        //- Update properties
        virtual void correct();

        //- Update densities for given pressure change
        void correctRho(const volScalarField& dp);
*/
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
