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
          fvMesh       const& mesh
        , porousMedium      & porous_medium
        , word         const& name = "geochemistryTransportOnly"
    );

        void 
    initialize () override;

        void 
    update () override;
};

} // namespace geochemistryModels
} // namespace Foam
