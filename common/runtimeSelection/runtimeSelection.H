#pragma once

#define OPENFOAM_RUNTIME_SELECTOR_DECLARATION(MODELNAME)                      \
    declareRunTimeSelectionTable (                                            \
          autoPtr                                                             \
        , MODELNAME                                                           \
        , dictionary                                                          \
        , (const fvMesh& mesh , porousMedia& parent)                          \
        , (mesh , parent)                                                     \
    );                                                                        \
                                                                              \
        static autoPtr<MODELNAME>                                             \
    New (const fvMesh& mesh, porousMedia& parent);                            \
                                                                              
#define OPENFOAM_RUNTIME_SELECTOR_IMPLEMENTATION(MODELNAME)                   \
namespace Foam                                                                \
{                                                                             \
    defineTypeNameAndDebug (MODELNAME, 0);                                    \
    defineRunTimeSelectionTable (MODELNAME , dictionary);                     \
                                                                              \
        Foam::autoPtr<Foam::MODELNAME>                                        \
    Foam::MODELNAME::New (const fvMesh& mesh, porousMedia& parent)            \
    {                                                                         \
                                                                              \
        const word modelType = parent.dict ().lookup (#MODELNAME);            \
                                                                              \
        Info<< "Selecting absolute permeability model " << modelType << endl; \
                                                                              \
        typename dictionaryConstructorTable::iterator cstrIter =              \
            dictionaryConstructorTablePtr_->find (modelType);                 \
                                                                              \
        if (cstrIter == dictionaryConstructorTablePtr_->end ())               \
        {                                                                     \
            FatalErrorInFunction                                              \
                << "Unknown "#MODELNAME" type "                               \
                << modelType << nl << nl                                      \
                << "Valid "#MODELNAME" types:" << endl                        \
                << dictionaryConstructorTablePtr_->sortedToc ()               \
                << exit (FatalError);                                         \
        }                                                                     \
                                                                              \
        return autoPtr<MODELNAME>                                             \
        (                                                                     \
            cstrIter ()(                                                      \
                mesh,                                                         \
                parent                                                        \
            )                                                                 \
        );                                                                    \
    }                                                                         \
}                                                                             \
                                                                              
#define OPENFOAM_RUNTIME_SELECTOR_ADD(MODELNAME,MODEL)                        \
defineTypeNameAndDebug (MODEL, 0);                                            \
addToRunTimeSelectionTable (MODELNAME, MODEL, dictionary);                    \
                                                                              
