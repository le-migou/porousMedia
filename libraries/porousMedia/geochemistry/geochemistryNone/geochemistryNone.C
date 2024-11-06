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

#include "geochemistryNone.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedia.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace geochemistryModels
{
    defineTypeNameAndDebug(geochemistryNone, 0);
    addToRunTimeSelectionTable(geochemistryModel, geochemistryNone, dictionary);
}
}

namespace Foam
{
namespace geochemistryModels
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

geochemistryNone::geochemistryNone(
    fvMesh const& mesh,
    porousMedia& parent
)
: 
    geochemistryModel(
        mesh, 
        parent
    ), 
    coeffDict_(parent.dict().subDict(type() + "Coeffs")), 
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
bool geochemistryNone::read()
{
    return false;
}
*/
volScalarField const& geochemistryNone::eps() const
{
    return eps_;
}

volScalarField const& geochemistryNone::rho() const
{
    return fluidThermo_.rho();
}

volScalarField const& geochemistryNone::mu() const
{
    return fluidThermo_.mu();
}

volScalarField const& geochemistryNone::massSourceTerm() const
{
    return massSourceTerm_;
}

/*
void geochemistryNone::correct()
{}
*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace geochemistryModels
} // End namespace Foam

// ************************************************************************* //
