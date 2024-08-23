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
    Foam::compressibleDarcyPhase

Description
    Single compressible phase derived from the compressibleVoFphase.

    Used in compressibleMultiphaseDarcyMixture for multiphase Darcy simulations.

SourceFiles
    compressibleDarcyPhase.C

See also
    Foam::compressibleMultiphaseDarcyMixture

\*---------------------------------------------------------------------------*/

#ifndef compressibleDarcyPhase_H
#define compressibleDarcyPhase_H

#include "compressibleVoFphase.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                            Class compressibleDarcyPhase Declaration
\*---------------------------------------------------------------------------*/

class compressibleDarcyPhase
:
    public compressibleVoFphase
{
    // Private Data

        //- Velocity
        volVectorField U_;

public:

    // Constructors

        //- Construct from components
        compressibleDarcyPhase
        (
            const word& name,
            const fvMesh& mesh,
            const volScalarField& T
        );
        /*
        //- Return clone
        virtual autoPtr<DarcyPhase> clone() const;

        //- Return a pointer to a new compressibleDarcyPhase
        //  created on freestore from Istream
        class iNew
        :
            public DarcyPhase::iNew
        {
            const volScalarField& T_;

        public:

            iNew(const fvMesh& mesh, const volScalarField& T)
            :
                DarcyPhase::iNew(mesh),
                T_(T)
            {}

            virtual autoPtr<DarcyPhase> operator()(Istream& is) const
            {
                const word name(is);

                return autoPtr<DarcyPhase>
                (
                    new compressibleDarcyPhase(name, mesh_, T_)
                );
            }
        };

    // Member Functions

        //- Return const-access to phase rhoThermo
        const rhoThermo& thermo() const
        {
            return thermo_();
        }

        //- Return access to phase rhoThermo
        rhoThermo& thermo()
        {
            return thermo_();
        }

        //- Return const-access to phase mass-fraction
        const volScalarField& Alpha() const
        {
            return Alpha_;
        }

        //- Return access to phase mass-fraction
        volScalarField& Alpha()
        {
            return Alpha_;
        }

        //- Return const-access to phase divergence
        const volScalarField::Internal& dgdt() const
        {
            return dgdt_;
        }

        //- Return access to phase divergence
        volScalarField::Internal& dgdt()
        {
            return dgdt_;
        }

        void correct
        (
            const volScalarField& p,
            const volScalarField& T
        );
        */
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
