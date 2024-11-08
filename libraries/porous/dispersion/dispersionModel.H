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
soluteMedium;

    class 
dispersionModel
    : public nonCopyable
    , public modelBase <soluteMedium>
{
public:
    TypeName ("dispersion");
    OPENFOAM_RUNTIME_SELECTOR_DECLARATION(dispersionModel, soluteMedium)

    dispersionModel (
          const fvMesh& mesh
        , soluteMedium& parent
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
