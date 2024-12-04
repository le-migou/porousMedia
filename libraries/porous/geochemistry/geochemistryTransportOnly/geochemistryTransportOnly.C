#include "geochemistryTransportOnly.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedium.H"
#include "fvm.H"
#include "fvc.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

OPENFOAM_RTS_MODEL_ADD(geochemistryModel, geochemistryTransportOnly)

geochemistryTransportOnly::geochemistryTransportOnly (
      fvMesh       const& mesh
    , porousMedium      & porous_medium
    , word         const& name
)
    : geochemistryNone { mesh, porous_medium, name }
{
    porous_medium.solutes ().add_model <dispersionModel> ("dispersion");
}

    void
geochemistryTransportOnly::initialize ()
{
    // Nothing to do here
}

    void
geochemistryTransportOnly::update ()
{
    forAll (porous_medium ().solutes (), soluteIndex)
    {
            auto const&
        solute = porous_medium ().solute (soluteIndex);
            auto&
        C = solute.concentration ();
            auto const& 
        eps_ = porosity ();
            auto const&
        phiRho = porous_medium ().velocity_flux ();
            auto const 
        rhof = fvc::interpolate (porous_medium ().density ());
            auto const
        phi = phiRho / rhof;
        /* Or
            auto const
        phi = fvc::flux (porous_medium (). U());
        */
            auto const&
        D = solute.dispersion ();
        fvScalarMatrix Ceqn
        (
              fvm::ddt (eps_, C) 
            + fvm::div (phi, C, "div(phi,C)") 
            - fvm::laplacian (eps_ * D, C, "laplacian(eps*D,C)")
        );
        Ceqn.relax ();
        Ceqn.solve ();
    }
}

} // namespace geochemistryModels
} // namespace Foam
