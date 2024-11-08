#pragma once
#include "modelBase.H"
#include "runtimeSelection.H"
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
dispersionModel
    : public nonCopyable
    , public modelBase <porousMedia>
{
public:
    TypeName ("dispersion");
    OPENFOAM_RUNTIME_SELECTOR_DECLARATION(dispersionModel)

    dispersionModel (
          const fvMesh& mesh
        , porousMedia& parent
        , word const& name
    )
        : modelBase { parent, name }
    {}

        virtual 
    ~dispersionModel () = default;

    // Dispersion tensor
        virtual volTensorField const& 
    D () const = 0;
};
} // namespace Foam
