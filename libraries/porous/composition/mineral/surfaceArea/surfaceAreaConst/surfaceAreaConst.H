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
    A0_;
        volTensorField 
    A_;

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
    A () const override
    {
        return A_;
    }
};

} // namespace surfaceAreaModels
} // namespace Foam
