#include "geochemistryTransportOnly.H"
#include "addToRunTimeSelectionTable.H"
#include "porousMedia.H"
#include "fvm.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

OPENFOAM_RUNTIME_SELECTOR_ADD(geochemistryModel, geochemistryTransportOnly)

geochemistryTransportOnly::geochemistryTransportOnly (
      fvMesh const& mesh
    , porousMedia& parent
    , word const& name
)
    : geochemistryNone { mesh, parent, name }
{
    /*
    forAll (this->parent ().solutes(), i)
    {
    }
    */
}

    void
geochemistryTransportOnly::update ()
{
    /*
    forAll (parent().solutes(), i)
    {
            volScalarField&
        C = parent().soluteConcentration(i);
        fvScalarMatrix Ceqn
        (
            fvm::ddt(eps_, C) + fvm::div(phi_, C, "divPhiC")
            - fvm::laplacian(eps_ * D, C, "laplacianDC")
        );

    }
    */
}

} // namespace geochemistryModels
} // namespace Foam
