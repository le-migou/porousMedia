#pragma once
#include "geochemistryNone.H"
#include "dispersionModel.H"

    namespace 
Foam
{
    namespace 
geochemistryModels
{

    class 
geochemistryTransportOnly
    : public geochemistryNone
{
        PtrList <dispersionModel>
    dispersionModels_;
public:

    TypeName ("geochemistryTransportOnly");

    geochemistryTransportOnly (
          fvMesh const& mesh
        , porousMedium& parent
        , word const& name = "geochemistryTransportOnly"
    );

    ~geochemistryTransportOnly ()
    {}

        void 
    update () override;
};

} // namespace geochemistryModels
} // namespace Foam
