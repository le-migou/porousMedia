#pragma once
#include "nonCopyable.H"
#include "fluid.H"
#include "porousMedium.H"

namespace Foam
{
namespace solvers
{
    class 
darcy
    : public fluid
    , public nonCopyable
{
        porousMedium 
    porousMedium_;

    //- The inverse of the permeability tensor
    // FIXME: this is scalar ATM, I don't have a solution for adding an
    // implicit source which is a tensor.
        volScalarField 
    muInvK_;

        void 
    continuityErrors ();
        void 
    correctDensity ();
        void 
    correctPressure ();
        void 
    correctBuoyantPressure ();
        void 
    updatePorousMedium ()
    {
        porousMedium_.update ();
    }

public:
    TypeName ("darcy");

    darcy (fvMesh& mesh)
        : fluid { mesh }
        , porousMedium_ { mesh }
        , muInvK_ { 
              momentumTransport->nu() * momentumTransport->rho() 
            / porousMedium_.K ().component (tensor::XX)
          }
    {}

    virtual ~darcy() = default;

        void 
    momentumPredictor() override;
        void 
    pressureCorrector() override;
};
} // namespace solvers
} // namespace Foam
