#pragma once
#include "../absolutePermeabilityModel.H"
#include "dimensionedTensor.H"
#include "volFields.H"

    namespace 
Foam
{
    namespace 
absolutePermeabilityModels
{
    class 
absolutePermeabilityConst
    : public absolutePermeabilityModel
{
        dimensionedTensor 
    K0_;
        volTensorField 
    K_;

public:
    TypeName ("absolutePermeabilityConst");

    absolutePermeabilityConst (
          const fvMesh& mesh
        , porousMedium& parent
        , word const& name = "absolutePermeabilityConst"
    );

    ~absolutePermeabilityConst ()
    {}

    volTensorField const& K () const override
    {
        return K_;
    }
};

} // namespace absolutePermeabilityModels
} // namespace Foam
