#include "UList.H"
#include "geochemistryFirstOrderKinetic.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedium.H"
#include "fvm.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

OPENFOAM_RTS_MODEL_ADD(geochemistryModel, geochemistryFirstOrderKinetic)

geochemistryFirstOrderKinetic::geochemistryFirstOrderKinetic (
      fvMesh       const& mesh
    , porousMedium      & porous_medium
    , word         const& name
)
    : geochemistryModel { mesh, porous_medium, name }
    , porosity_ {
            IOobject {
              "porosity"
            , mesh.time ().name ()
            , mesh
            , IOobject::NO_READ
            , IOobject::AUTO_WRITE
            }
        , mesh
        , dimensionedScalar { dimless, 0 }
      }
    , old_porosity_ { porosity_ }
{
    porous_medium.solutes ().add_model <surfaceAreaModel> ("surfaceArea");
    porous_medium.soluteMineralPairs ().add_model <reactionRateModel> ("reactionRate");
}

    void
geochemistryFirstOrderKinetic::initialize ()
{
    update_porosity ();
}


    void
geochemistryFirstOrderKinetic::update_porosity ()
{
    old_porosity_ = porosity_;
    porosity_ = porous_medium_.minerals ().inertVolumeFraction ();
    forAll (porous_medium_.minerals (), mineralIndex)
    {
        porosity_ += porous_medium_.mineral (mineralIndex).volumeFraction ();
    }
    porosity_ = 1. - porosity_;
}

    void
geochemistryFirstOrderKinetic::update ()
{
    // Solutes
    forAll (porous_medium ().solutes (), soluteIndex)
    {
            auto const&
        solute = porous_medium ().solute (soluteIndex);
            auto&
        C = solute.concentration ();
            auto const&
        phiRho = porous_medium ().velocity_flux ();
            auto const 
        rhof = fvc::interpolate (porous_medium ().density ());
            auto const
        phi = phiRho / rhof;
        /* Or
            auto const
        phi = fvc::flux (porous_medium ().velocity());
        */
            auto const&
        D = solute.dispersion ();
            auto
        Ak = volScalarField { 
              IOobject {
                "Ak"
                , porous_medium ().mesh ().time ().name ()
                , porous_medium ().mesh ()
                , IOobject::NO_READ
                , IOobject::NO_WRITE
              }
            , porous_medium ().mesh ()
            , dimensionedScalar (dimless / dimTime, 0)
        };
        forAll (porous_medium ().minerals (), mineralIndex)
        {
                const auto&
            mineral = porous_medium ().mineral (mineralIndex);
                const auto&
            soluteMineralPair = porous_medium ().soluteMineralPair (
                  soluteIndex
                , mineralIndex
            );
            Ak += mineral.surface_area () 
                * soluteMineralPair.reaction_rate ();
        }
            auto 
        Ceqn = fvScalarMatrix
        {
              fvm::ddt (porosity_, C) 
            + fvm::div (phi, C, "div(phi,C)") 
            - fvm::laplacian (porosity_ * D, C, "laplacian(eps*D,C)")
            - fvm::Sp (Ak, C)
        };
        Ceqn.relax ();
        Ceqn.solve ();
    }
    // Minerals
    forAll (porous_medium ().minerals (), mineralIndex)
    {
            const auto&
        mineral = porous_medium ().mineral (mineralIndex);
            auto&
        Ys = mineral.volumeFraction ();
            auto
        dM = volScalarField { 
              IOobject {
                  "dM"
                , porous_medium ().mesh ().time ().name ()
                , porous_medium ().mesh ()
                , IOobject::NO_READ
                , IOobject::NO_WRITE
              }
            , porous_medium ().mesh ()
            , dimensionedScalar (dimless / dimTime, 0)
        };
        forAll (porous_medium ().solutes (), soluteIndex)
        {
                auto&
            C = porous_medium ().solute (soluteIndex).concentration ();
                const auto&
            soluteMineralPair = porous_medium ().soluteMineralPair (
                  soluteIndex
                , mineralIndex
            );
            dM += mineral.surfaceArea () 
                * soluteMineralPair.reactionRate ()
                * mineral.molarVolume ()
                * C
            ;
        }
            auto 
        Meqn = fvScalarMatrix
        {
              fvm::ddt (Ys) 
            ==
              fvm::Sp (dM, Ys)
        };
        Meqn.relax ();
        Meqn.solve ();
    }
    update_porosity ();
}

} // namespace geochemistryModels
} // namespace Foam
