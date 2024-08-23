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

#include "multiphaseGeochemistryNone.H"
#include "addToRunTimeSelectionTable.H"
#include "multiphasePorousMedia.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace multiphaseGeochemistryModels
{
    defineTypeNameAndDebug(multiphaseGeochemistryNone, 0);
    addToRunTimeSelectionTable(multiphaseGeochemistryModel, multiphaseGeochemistryNone, dictionary);
}
}

namespace Foam
{
namespace multiphaseGeochemistryModels
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

multiphaseGeochemistryNone::multiphaseGeochemistryNone(
    fvMesh const& mesh,
    multiphasePorousMedia* parent
)
: 
    multiphaseGeochemistryModel(
        mesh, 
        parent
    ), 
    mixture_(parent->mixture ()),
    coeffDict_(parent->subDict(type() + "Coeffs")), 
    eps0_("eps0", dimless, coeffDict_), 
    eps_
    (
      IOobject
      (
          "eps",
          mesh.time().name(),
          mesh,
          IOobject::NO_READ,
          IOobject::NO_WRITE
      ),
      mesh,
      eps0_
    ),
    massSourceTerm_
    (
      IOobject
      (
          "massSourceTerm",
          mesh.time().name(),
          mesh,
          IOobject::NO_READ,
          IOobject::NO_WRITE
      ),
      mesh,
      dimensionedScalar(dimless/dimTime, 0)
    )
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
/*
bool multiphaseGeochemistryNone::read()
{
    return false;
}
*/
/*
void multiphaseGeochemistryNone::correct()
{}
*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace multiphaseGeochemistryModels
} // End namespace Foam

// ************************************************************************* //
