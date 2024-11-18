#pragma once
#include "../surfaceAreaModel.H"
#include "dimensionedTensor.H"
#include "volFields.H"

    namespace 
Foam
{
    namespace 
surfaceAreaModels
{
    class 
surfaceAreaConst
    : public surfaceAreaModel
{
        dimensionedTensor 
    D0_;
        volTensorField 
    D_;

public:
    TypeName ("surfaceAreaConst");

    surfaceAreaConst (
          const fvMesh& mesh
        , mineralMedium& parent
        , word const& name = "surfaceAreaConst"
    );

    ~surfaceAreaConst ()
    {}

        volTensorField const& 
    D () const override
    {
        return D_;
    }
};

} // namespace surfaceAreaModels
} // namespace Foam
