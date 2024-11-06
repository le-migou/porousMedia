#ifndef absolutePermeabilityModel_H
#define absolutePermeabilityModel_H

#include "nonCopyable.H"
#include "dictionary.H"
#include "fvMesh.H"
#include "volFieldsFwd.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class porousMedia;

class absolutePermeabilityModel
    : public nonCopyable
{
    const porousMedia& parent_;

public:
    TypeName("absolutePermeability");

    declareRunTimeSelectionTable
    (
        autoPtr,
        absolutePermeabilityModel,
        dictionary,
        (
            const fvMesh& mesh,
            porousMedia& parent
        ),
        (
            mesh, 
            parent
        )
    );

    absolutePermeabilityModel(
        const fvMesh& mesh, 
        porousMedia& parent
    );

    // Selectors

        //- Return a reference to the selected absolute permeability model
        static autoPtr<absolutePermeabilityModel> New
        (
            const fvMesh& mesh,
            porousMedia& parent
        );


    //- Destructor
    virtual ~absolutePermeabilityModel()
    {}


    // Member Functions
        /*
        //- Read model coefficients if they have changed
        virtual bool read() = 0;
        */

        //- Return the absolute permeability
        virtual volTensorField const& K() const = 0;

        /*
        //- Solve the turbulence equations and correct the turbulence viscosity
        virtual void correct() = 0;
        */


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const absolutePermeabilityModel&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// #ifdef NoRepository
//     #include "absolutePermeabilityModel.C"
// #endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
