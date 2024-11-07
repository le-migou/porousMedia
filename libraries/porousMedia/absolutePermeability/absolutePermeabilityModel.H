#pragma once
#include "nonCopyable.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"

    namespace 
Foam
{
    class 
porousMedia;

    class 
absolutePermeabilityModel
    : public nonCopyable
{
        const porousMedia& 
    parent_;

public:
    TypeName ("absolutePermeability");

    declareRunTimeSelectionTable (
          autoPtr
        , absolutePermeabilityModel
        , dictionary
        , (const fvMesh& mesh , porousMedia& parent)
        , (mesh , parent)
    );

        static autoPtr<absolutePermeabilityModel> 
    New (const fvMesh& mesh, porousMedia& parent);

    absolutePermeabilityModel (const fvMesh& mesh, porousMedia& parent)
        : parent_ (parent)
    {}

        virtual 
    ~absolutePermeabilityModel ()
    {}

        // Absolute permeability
            virtual volTensorField const& 
        K () const = 0;

};
} // namespace Foam
