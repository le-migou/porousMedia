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

OPENFOAM_RUNTIME_SELECTOR_ADD(geochemistryModel, geochemistryTransportOnly)

geochemistryTransportOnly::geochemistryTransportOnly (
      fvMesh const& mesh
    , porousMedium& parent
    , word const& name
)
    : geochemistryNone { mesh, parent, name }
{
    POROUS_MEDIA_REQUIRES_SOLUTE_MODEL(dispersion)
}

    void
geochemistryTransportOnly::update ()
{
    forAll (parent ().solutes (), i)
    {
            auto const&
        solute = parent ().solute (i);
            auto&
        C = solute.concentration ();
            auto const& 
        eps_ = eps ();
            auto const&
        phiRho = parent ().phi ();
            auto const 
        rhof = fvc::interpolate (parent ().rho ());
            auto const
        phi = phiRho / rhof;
        /* Or
            auto const
        phi = fvc::flux (parent (). U());
        */
            auto const&
        D = solute.D ();
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
