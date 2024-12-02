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
    , eps_ {
            IOobject {
              "eps"
            , mesh.time ().name ()
            , mesh
            , IOobject::NO_READ
            , IOobject::AUTO_WRITE
            }
        , mesh
        , dimensionedScalar { dimless, 0 }
      }
{
    porous_medium.solutes ().add_model <surfaceAreaModel> ("surfaceArea");
    porous_medium.soluteMineralPairs ().add_model <reactionRateModel> ("reactionRate");
    // FIXME: this goes in initialize()
    // update_porosity ();
}

    void
geochemistryFirstOrderKinetic::update_porosity ()
{
    eps_ = porous_medium_.minerals ().inertVolumeFraction ();
    forAll (porous_medium_.minerals (), mineralIndex)
    {
        eps_ += porous_medium_.mineral (mineralIndex).volumeFraction ();
    }
    eps_ = 1. - eps_;
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
        phiRho = porous_medium ().phi ();
            auto const 
        rhof = fvc::interpolate (porous_medium ().rho ());
            auto const
        phi = phiRho / rhof;
        /* Or
            auto const
        phi = fvc::flux (porous_medium (). U());
        */
            auto const&
        D = solute.D ();
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
            Ak += mineral.surfaceArea () 
                * soluteMineralPair.reactionRate ();
        }
            auto 
        Ceqn = fvScalarMatrix
        {
              fvm::ddt (eps_, C) 
            + fvm::div (phi, C, "div(phi,C)") 
            - fvm::laplacian (eps_ * D, C, "laplacian(eps*D,C)")
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
