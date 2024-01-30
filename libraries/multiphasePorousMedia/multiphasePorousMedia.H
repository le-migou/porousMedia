/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2022-2023 OpenFOAM Foundation
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
    Foam::multiphasePorousMedia

Description
    A class modelling a porous media. Encapsulates models for the geochemistry 
    and absolute permeability.

SourceFiles
    multiphasePorousMedia.C

\*---------------------------------------------------------------------------*/

#ifndef multiphasePorousMedia_H
#define multiphasePorousMedia_H

#include "IOdictionary.H"
#include "geochemistryModel.H"
#include "absolutePermeabilityModel.H"
#include "uniformDimensionedFields.H"
#include "compressibleMultiphaseVoFMixture.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
class fvMesh;

/*---------------------------------------------------------------------------*\
                       Class multiphasePorousMedia Declaration
\*---------------------------------------------------------------------------*/

class multiphasePorousMedia
:
    IOdictionary
{
    // Private member data

        //- Reference to the multiphaseVoFMixture
        autoPtr <compressibleMultiphaseVoFMixture> 
            compressibleMultiphaseVoFMixture_;

        //- Reference to the phases
        UPtrListDictionary<compressibleVoFphase>& compressibleVoFphases_;


        // Model for the geochemistry
        autoPtr <geochemistryModel> geochemistryModel_;

        // Model for the absolute permeability
        autoPtr <absolutePermeabilityModel> absolutePermeabilityModel_;

        //- Gravitational acceleration
        uniformDimensionedVectorField g_;


public:

    //- Runtime type information
        TypeName("multiphasePorousMedia");

    // Constructors

        //- Construct from components
        multiphasePorousMedia
        (
            const fvMesh& mesh
        );

        //- Disallow default bitwise copy construction
        multiphasePorousMedia(const multiphasePorousMedia&) = delete;

    //- Destructor
    virtual ~multiphasePorousMedia()
    {}


    // Member Functions

        static IOobject findModelDict
        (
            const objectRegistry& obr,
            bool registerObject = false
        );

        /*
        // - Read multiphasePorousMedia dictionary
        virtual bool read();
        */

        //- Pressure
        /*
        volScalarField& p()
        {
            return fluidThermo_->p();
        }
        */

        //- Porosity
        volScalarField const& eps() const
        {
            return geochemistryModel_->eps();
        }

        //- Absolute permeability
        volTensorField const& K() const
        {
            return absolutePermeabilityModel_->K();
        }

        //- Density of the fluid
        volScalarField const& rho() const
        {
            return geochemistryModel_->rho();
        }

        //- Viscosity of the fluid
        volScalarField const& mu() const
        {
            return geochemistryModel_->mu();
        }

        //- Source term for the flow solver
        volScalarField const& massSourceTerm() const
        {
            return geochemistryModel_->massSourceTerm();
        }

        //- Gravitational acceleration
        uniformDimensionedVectorField const& g() const
        {
            return g_;
        }


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const multiphasePorousMedia&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
