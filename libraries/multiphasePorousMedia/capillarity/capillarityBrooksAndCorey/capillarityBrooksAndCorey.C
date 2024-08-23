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

#include "capillarityBrooksAndCorey.H"
#include "addToRunTimeSelectionTable.H"
#include "multiphasePorousMedia.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace capillarityModels
{
    defineTypeNameAndDebug(capillarityBrooksAndCorey, 0);
    addToRunTimeSelectionTable(capillarityModel, capillarityBrooksAndCorey, dictionary);
}
}

namespace Foam
{
namespace capillarityModels
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

capillarityBrooksAndCorey::capillarityBrooksAndCorey(
    fvMesh const& mesh,
    multiphasePorousMedia* parent
)
: 
    capillarityModel(
        mesh, 
        parent
    ), 
    coeffDict_(parent_->subDict(type() + "Coeffs")),
    Se_(parent->Se()),
    dSedS_(parent->dSedS())
{
    for (int i = 1; i < phases_.size(); ++i)
    {
        word interface_name = phases_[0].name () + "." + phases_[i].name ();
        dictionary interface_dict = coeffDict_.subDict(interface_name);
        pc0_.append (
            interface_dict.lookup <scalar> ("pc0")
        );
        alpha_.append (
            interface_dict.lookup <scalar> ("alpha")
        );
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

//- ?
void capillarityBrooksAndCorey::correct ()
{
    for (int i = 1; i < phases_.size(); ++i)
    {
        pc_[i] = pc0_[i] * pow(Se_[i], -alpha_[i]);
        dpcdS_[i] = -alpha_[i] * pc0_[i] 
            * (pow(Se_[i], -alpha_[i] - 1.)) * dSedS_[i];
    }
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace capillarityModels
} // End namespace Foam

// ************************************************************************* //
