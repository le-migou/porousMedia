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
mineralMedium;

    class 
surfaceAreaModel
    : public nonCopyable
    , public modelBase <mineralMedium>
{
public:
    TypeName ("surfaceArea");
    OPENFOAM_RUNTIME_SELECTOR_DECLARATION(surfaceAreaModel, mineralMedium)

    surfaceAreaModel (
          const fvMesh& mesh
        , mineralMedium& parent
        , word const& name
    )
        : modelBase { parent, name }
    {}

        virtual 
    ~surfaceAreaModel () = default;

    // Dispersion tensor
        virtual volTensorField const& 
    D () const = 0;
};
} // namespace Foam
