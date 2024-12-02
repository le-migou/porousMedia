#pragma once
#include "base.H"
#include "modelBase.H"
// See below
// #include "HashPtrTable.H"
#include <unordered_map>
#include <cassert>
#include <iostream>

    namespace
Foam
{
    class
mediumBase
    : public base
{
    // Optional models management
    //
    // I was not able to make it work using OpenFOAM's library
    /*
        HashPtrTable <modelBase <mediumBase <mediumParent>>>
    models_;
    */

    // So here it is using the standard library.
    // FIXME: consider swtiching to std::unique_ptr
        std::unordered_map <std::string, base*>
    models_;

public:
    mediumBase (
          fvMesh       const& mesh
        , porousMedium const& porous_medium
        , word         const& name
    );

        void
    initialize () override
    {
        for (auto iter: models_)
        {
            assert (iter.second != nullptr);
            iter.second->initialize ();
        }
    }

        template <class Medium, class Model>
        void
    add_model (word const& name)
    {
            const auto
        iter = models_.find (name);
        if (iter != models_.end ()) return;
        /*
            auto
        p = Model::New (
                  this->mesh ()
                , porous_medium ()
                , *(dynamic_cast <Medium*> (this))
            );
            const auto
        p2 = p.ptr ();
        std::cout << "++++++++++++++++" << p2 << '\n';
            const auto
        p3 = dynamic_cast <modelBase*> (p2);
        std::cout << "++++++++++++++++" << p3 << '\n';
        std::cout << "++++++++++++++++" << name << '\n';
        models_[name] = p3;
        std::cout << "++++++++++++++++" << models_.at (name) << '\n';
        */
        models_[name] = dynamic_cast <modelBase*> (
            Model::New (
                  this->mesh ()
                , porous_medium ()
                , *(dynamic_cast <Medium*> (this))
            ).ptr ()
        );
    }
        template <class Model>
        Model const*
    get_model (word const& name) const
    {
        return dynamic_cast <Model const*> (models_.at (name));
    }
        template <class Model>
        Model*
    get_model (word const& name)
    {
        return dynamic_cast <Model*> (models_[name]);
    }
};
} // namespace Foam
