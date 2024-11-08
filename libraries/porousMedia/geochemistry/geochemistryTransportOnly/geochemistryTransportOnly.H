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
        , porousMedia& parent
        , word const& name = "geochemistryTransportOnly"
    );

    ~geochemistryTransportOnly ()
    {}

        void 
    update () override;
};

} // End namespace geochemistryModels
} // End namespace Foam
