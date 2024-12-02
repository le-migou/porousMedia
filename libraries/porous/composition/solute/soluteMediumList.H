#pragma once
#include "mediumList.H"
#include "soluteMedium.H"

    namespace
Foam
{
    class porousMedium;

    class
soluteMediumList
    : public mediumList <soluteMedium>
{
public:
    soluteMediumList (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
    );
};
} // namespace Foam
