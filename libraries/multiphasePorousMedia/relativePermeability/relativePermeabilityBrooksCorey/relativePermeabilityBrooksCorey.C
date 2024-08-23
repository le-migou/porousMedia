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

\*---------------------------------------------------------------------------*/

#include "relativePermeabilityBrooksCorey.H"
#include "addToRunTimeSelectionTable.H"
#include "multiphasePorousMedia.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace relativePermeabilityModels
{
    defineTypeNameAndDebug(relativePermeabilityBrooksCorey, 0);
    addToRunTimeSelectionTable(relativePermeabilityModel, relativePermeabilityBrooksCorey, dictionary);
}
}

namespace Foam
{
namespace relativePermeabilityModels
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

relativePermeabilityBrooksCorey::relativePermeabilityBrooksCorey(
    fvMesh const& mesh,
    multiphasePorousMedia* parent
)
: 
    relativePermeabilityModel(
        mesh, 
        parent
    ), 
    coeffDict_(parent->subDict(type() + "Coeffs"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

volScalarField const& relativePermeabilityBrooksCorey::krs(label phase_index) const
{

}

volScalarField const& relativePermeabilityBrooksCorey::dkrdSs(label phase_index) const
{

}

surfaceScalarField const& relativePermeabilityBrooksCorey::krfs(label phase_index) const
{

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace relativePermeabilityModels
} // End namespace Foam

// ************************************************************************* //
