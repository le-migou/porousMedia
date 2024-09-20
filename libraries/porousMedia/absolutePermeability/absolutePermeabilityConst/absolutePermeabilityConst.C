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

#include "volFields.H"
#include "absolutePermeabilityConst.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace absolutePermeabilityModels
{
    defineTypeNameAndDebug(absolutePermeabilityConst, 0);
    addToRunTimeSelectionTable(absolutePermeabilityModel, absolutePermeabilityConst, dictionary);
}
}

namespace Foam
{
namespace absolutePermeabilityModels
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

absolutePermeabilityConst::absolutePermeabilityConst(
    const fvMesh& mesh,
    const dictionary& dict
)
: 
    absolutePermeabilityModel(
        mesh,
        dict
    ),
    coeffDict_(dict.subDict(type() + "Coeffs")), 
    K0_("K0", dimLength * dimLength, coeffDict_), 
    K_
    (
      IOobject
      (
          "K",
          mesh.time().name(),
          mesh,
          IOobject::READ_IF_PRESENT,
          IOobject::AUTO_WRITE
      ),
      mesh,
      K0_,
      "zeroGradient"
    )
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
/*
bool absolutePermeabilityConst::read()
{
    return false;
}
*/
volTensorField const& absolutePermeabilityConst::K() const
{
    return K_;
}
/*
void absolutePermeabilityConst::correct()
{}
*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace absolutePermeabilityModels
} // End namespace Foam

// ************************************************************************* //
