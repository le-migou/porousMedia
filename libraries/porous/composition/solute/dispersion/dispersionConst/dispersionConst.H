#pragma once
#include "../dispersionModel.H"
#include "dimensionedTensor.H"
#include "volFields.H"

    namespace 
Foam
{
    namespace 
dispersionModels
{
    class 
dispersionConst
    : public dispersionModel
{
        dimensionedTensor 
    D0_;
        volTensorField 
    D_;

public:
    TypeName ("dispersionConst");

    dispersionConst (
          const fvMesh& mesh
        , soluteMedium& parent
        , word const& name = "dispersionConst"
    );

    ~dispersionConst ()
    {}

        volTensorField const& 
    D () const override
    {
        return D_;
    }
};

} // namespace dispersionModels
} // namespace Foam
