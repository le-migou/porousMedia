#pragma once

#define OPENFOAM_RTS_MODEL_DECLARATION(MODELNAME)            \
    declareRunTimeSelectionTable (                           \
          autoPtr                                            \
        , MODELNAME                                          \
        , dictionary                                         \
        , (const fvMesh& mesh , porousMedium& porous_medium) \
        , (mesh , porous_medium)                             \
    );                                                       \
                                                             \
        static autoPtr<MODELNAME>                            \
    New (const fvMesh& mesh, porousMedium& porous_medium);   \
                                                                                    
#define OPENFOAM_RTS_MEDIUM_MODEL_DECLARATION(MODELNAME,MEDIUM)                         \
    declareRunTimeSelectionTable (                                                      \
          autoPtr                                                                       \
        , MODELNAME                                                                     \
        , dictionary                                                                    \
        , (const fvMesh& mesh, porousMedium const& porous_medium, MEDIUM const& medium) \
        , (mesh , porous_medium, medium)                                                \
    );                                                                                  \
                                                                                        \
        static autoPtr<MODELNAME>                                                       \
    New (const fvMesh& mesh, porousMedium const& porous_medium, MEDIUM const& medium);  \
                                                                                    
#define OPENFOAM_RTS_MODEL_IMPLEMENTATION(MODELNAME,MODELNICENAME)        \
namespace Foam                                                            \
{                                                                         \
    defineTypeNameAndDebug (MODELNAME, 0);                                \
    defineRunTimeSelectionTable (MODELNAME , dictionary);                 \
                                                                          \
        Foam::autoPtr<Foam::MODELNAME>                                    \
    Foam::MODELNAME::New (                                                \
          const fvMesh& mesh                                              \
        , porousMedium& porous_medium                                     \
    ){                                                                    \
                                                                          \
        const word modelType = porous_medium.dict ().lookup (#MODELNAME); \
                                                                          \
        Info<< "Selecting "#MODELNICENAME" model " << modelType << endl;  \
                                                                          \
        typename dictionaryConstructorTable::iterator cstrIter =          \
            dictionaryConstructorTablePtr_->find (modelType);             \
                                                                          \
        if (cstrIter == dictionaryConstructorTablePtr_->end ())           \
        {                                                                 \
            FatalErrorInFunction                                          \
                << "Unknown "#MODELNAME" type "                           \
                << modelType << nl << nl                                  \
                << "Valid "#MODELNAME" types:" << endl                    \
                << dictionaryConstructorTablePtr_->sortedToc ()           \
                << exit (FatalError);                                     \
        }                                                                 \
                                                                          \
        return autoPtr<MODELNAME>                                         \
        (                                                                 \
            cstrIter ()(                                                  \
                mesh,                                                     \
                porous_medium                                             \
            )                                                             \
        );                                                                \
    }                                                                     \
}                                                                         \
                                                                                    
#define OPENFOAM_RTS_MEDIUM_MODEL_IMPLEMENTATION(MODELNAME,MODELNICENAME,MEDIUM) \
namespace Foam                                                                   \
{                                                                                \
    defineTypeNameAndDebug (MODELNAME, 0);                                       \
    defineRunTimeSelectionTable (MODELNAME , dictionary);                        \
                                                                                 \
        Foam::autoPtr<Foam::MODELNAME>                                           \
    Foam::MODELNAME::New (                                                       \
          fvMesh const& mesh                                                     \
        , porousMedium const& porous_medium                                      \
        , MEDIUM const& medium                                                   \
    ){                                                                           \
                                                                                 \
        const word modelType = medium.dict ().lookup (#MODELNAME);               \
                                                                                 \
        Info<< "Selecting "#MODELNICENAME" model " << modelType << endl;         \
                                                                                 \
        typename dictionaryConstructorTable::iterator cstrIter =                 \
            dictionaryConstructorTablePtr_->find (modelType);                    \
                                                                                 \
        if (cstrIter == dictionaryConstructorTablePtr_->end ())                  \
        {                                                                        \
            FatalErrorInFunction                                                 \
                << "Unknown "#MODELNAME" type "                                  \
                << modelType << nl << nl                                         \
                << "Valid "#MODELNAME" types:" << endl                           \
                << dictionaryConstructorTablePtr_->sortedToc ()                  \
                << exit (FatalError);                                            \
        }                                                                        \
                                                                                 \
        return autoPtr<MODELNAME>                                                \
        (                                                                        \
            cstrIter ()(                                                         \
                mesh,                                                            \
                porous_medium,                                                   \
                medium                                                           \
            )                                                                    \
        );                                                                       \
    }                                                                            \
}                                                                                \
                                                                                    
#define OPENFOAM_RTS_MODEL_ADD(MODELNAME,MODEL)            \
defineTypeNameAndDebug (MODEL, 0);                         \
addToRunTimeSelectionTable (MODELNAME, MODEL, dictionary); \
                                                                                    
