#pragma once
#include "geochemistryNone.H"

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
public:

    TypeName ("geochemistryTransportOnly");

    geochemistryTransportOnly (
          fvMesh const& mesh
        , porousMedium& parent
        , word const& name = "geochemistryTransportOnly"
    );

    ~geochemistryTransportOnly () = default;

        void 
    update () override;
};

} // namespace geochemistryModels
} // namespace Foam
