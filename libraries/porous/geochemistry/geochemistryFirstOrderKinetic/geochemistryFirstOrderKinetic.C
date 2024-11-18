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

OPENFOAM_RUNTIME_SELECTOR_ADD(geochemistryModel, geochemistryFirstOrderKinetic)

geochemistryFirstOrderKinetic::geochemistryFirstOrderKinetic (
      fvMesh const& mesh
    , porousMedium& parent
    , word const& name
)
    : geochemistryModel { mesh, parent, name }
    // FIXME: how do I construct this as an empty field?
    , eps_ { parent.minerals ().inertVolumeFraction () }
{
    update_porosity ();
}

    void
geochemistryFirstOrderKinetic::update_porosity ()
{
    eps_ = parent_.minerals ().inertVolumeFraction ();
    forAll (parent_.minerals (), i)
    {
        eps_ += parent_.mineral (i).volumeFraction ();
    }
    eps_ = 1. - eps_;
}

    void
geochemistryFirstOrderKinetic::update ()
{
    forAll (parent ().solutes (), i)
    {
            auto const&
        solute = parent ().solute (i);
            auto&
        C = solute.concentration ();
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
            auto
        Ak = volScalarField { 
            IOobject {
                "Ys.inert"
                , parent ().mesh ().time ().name ()
                , parent ().mesh ()
                , IOobject::READ_IF_PRESENT
                , IOobject::AUTO_WRITE
            }
            , parent ().mesh ()
            , dimless / dimTime
            , 0
        };
        forAll (parent ().minerals (), i)
        {
                const auto&
            mineral = parent ().mineral (i);
            //Ak += mineral.surfaceArea () * mineral.rate () * mineral.activity ();
        }
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
