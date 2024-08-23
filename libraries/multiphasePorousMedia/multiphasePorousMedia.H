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
    A class modelling a porous media. Encapsulates models for the multiphaseGeochemistry 
    and absolute permeability.

SourceFiles
    multiphasePorousMedia.C

\*---------------------------------------------------------------------------*/

#ifndef multiphasePorousMedia_H
#define multiphasePorousMedia_H

#include "IOdictionary.H"
#include "multiphaseGeochemistryModel.H"
#include "relativePermeabilityModel.H"
#include "absolutePermeabilityModel.H"
#include "capillarityModel.H"
#include "reducedSaturationModel.H"
#include "uniformDimensionedFields.H"
#include "surfaceFields.H"

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
    public IOdictionary
{
    // Private member data

        //- Reference to the multiphaseDarcyPixture
        //  Provided by the solver
        compressibleMultiphaseVoFMixture& mixture_;

        //- Reference to the phases
        UPtrListDictionary<compressibleVoFphase>& phases_;

        // WARNING: these models might have dependencies between them so the order
        // of their construction is relevant.

        //- Model for the multiphaseGeochemistry
        autoPtr <multiphaseGeochemistryModel> multiphaseGeochemistryModel_;

        //- Model for thereduced Saturation
        autoPtr <reducedSaturationModel> reducedSaturationModel_;

        //- Model for the capillarity pressure
        autoPtr <capillarityModel> capillarityModel_;

        //- Model for the relative permeabilities
        autoPtr <absolutePermeabilityModel> absolutePermeabilityModel_;

        //- Model for the relative permeabilities
        autoPtr <relativePermeabilityModel> relativePermeabilityModel_;

        //- Gravitational acceleration
        uniformDimensionedVectorField g_;

        //- Saturations
        //  Provided by the solver
        PtrList<volScalarField> const& Ss_;

        //- ?
        surfaceScalarField Lf_;

        //- ?
        surfaceScalarField Mf_;

        //- ?
        PtrList <surfaceScalarField> Lfs_;

        //- ?
        PtrList <surfaceScalarField> Mfs_;

public:

    //- Runtime type information
        TypeName("multiphasePorousMedia");

    // Constructors

        //- Construct from components
        multiphasePorousMedia
        (
            const fvMesh& mesh,
            compressibleMultiphaseVoFMixture& mixture,
            PtrList<volScalarField> const& Ss
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

        // -?
        compressibleMultiphaseVoFMixture const& mixture() const
        {
            return mixture_;
        }
        compressibleMultiphaseVoFMixture& mixture()
        {
            return mixture_;
        }

        //- Reference to the phases
        UPtrListDictionary<compressibleVoFphase> const& phases() const
        {
            return phases_;
        }

        //- Pressure
        volScalarField& p()
        {
            return mixture_.p();
        }

        //- ?
        volScalarField const& Ss(label phase_index) const
        {
            return Ss_[phase_index];
        }

        //- ?
        PtrList<volScalarField> const& Ss() const
        {
            return Ss_;
        }

        //- Porosity
        volScalarField const& eps() const
        {
            return multiphaseGeochemistryModel_->eps();
        }
    //
        //- Absolute permeability
        volTensorField const& K() const
        {
            return absolutePermeabilityModel_->K();
        }

        //- Density of the fluid
        volScalarField const& rho() const
        {
            return multiphaseGeochemistryModel_->rho();
        }
        volScalarField const& rho(label phase_index) const
        {
            return multiphaseGeochemistryModel_->rho(phase_index);
        }

        //- Viscosity of the fluid
        volScalarField const& mu() const
        {
            return multiphaseGeochemistryModel_->mu();
        }
        volScalarField const& mu(label phase_index) const
        {
            return multiphaseGeochemistryModel_->mu(phase_index);
        }

        //- Source term for the flow solver
        volScalarField const& massSourceTerm() const
        {
            return multiphaseGeochemistryModel_->massSourceTerm();
        }

        //- Gravitational acceleration
        uniformDimensionedVectorField const& g() const
        {
            return g_;
        }

        //- ?
        surfaceScalarField const& Lf () const
        {
            return Lf_;
        }

        //- ?
        surfaceScalarField const& Mf () const
        {
            return Mf_;
        }

        //- ?
        surfaceScalarField const& Lfs (label phase_index) const
        {
            return Lfs_[phase_index];
        }

        //- ?
        surfaceScalarField const& Mfs (label phase_index) const
        {
            return Mfs_[phase_index];
        }

        //- ?
        volScalarField const& pc (label interface_index) const
        {
            return capillarityModel_->pc (interface_index);
        }

        //- ?
        PtrList <volScalarField> const& pc () const
        {
            return capillarityModel_->pc ();
        }

        //- ?
        volScalarField const& dpcdS (label interface_index) const
        {
            return capillarityModel_->dpcdS (interface_index);
        }

        //- ?
        PtrList <volScalarField> const& dpcdS () const
        {
            return capillarityModel_->dpcdS ();
        }

        //- Return relative permeabilities according
        volScalarField const& krs(label phase_index) const
        {
            return relativePermeabilityModel_->krs(phase_index);
        }

        //- Return the derivatives of relative permeabilities
        volScalarField const& dkrdSs(label phase_index) const
        {
            return relativePermeabilityModel_->dkrdSs(phase_index);
        }

        //- ?
        surfaceScalarField const& krfs(label phase_index) const
        {
            return relativePermeabilityModel_->krfs(phase_index);
        }

        //- Return an effective saturation
        volScalarField const& Se(label phase_index) const 
        {
            return reducedSaturationModel_->Se(phase_index);
        }

        //- Return the effective saturations
        PtrList <volScalarField> const& Se() const 
        {
            return reducedSaturationModel_->Se();
        }

        //- Return the derivative of an effective saturation
        volScalarField const& dSedS(label phase_index) const
        {
            return reducedSaturationModel_->dSedS(phase_index);
        }

        //- Return the derivative of the effective saturations
        PtrList <volScalarField> const& dSedS() const
        {
            return reducedSaturationModel_->dSedS();
        }

        

        //- ?
        void correct ();

    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const multiphasePorousMedia&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
