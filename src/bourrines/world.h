#pragma once

#include "system.h"

#include "stores/array_of_struct.h"
#include "stores/struct_of_array.h"

#include <boost/container/flat_set.hpp>

namespace bourrines {

    template<typename Store>
    class world {
    public:

        entity create_entity() {
            entity e;
            if (!recyclable_entities_.empty()) {
                e = recyclable_entities_.back();
                recyclable_entities_.pop_back();
                store_.recycle_entity(e);
            } else {
                e = store_.create_entity();
            }
            active_entities_.insert(e);
            return e;
        }

        void kill_entity(entity e) {
            active_entities_.erase(e);
            recyclable_entities_.push_back(e);
        }

        template< typename C >
        C& get(entity e) {
            return store_.get<C>(e);
        }

        template< typename C >
        const C& get(entity e) const {
            return store_.get<C>(e);
        }

        template< typename C >
        C& add(entity e) {
            return store_.add<C>(e);
        }

        template< typename C >
        void remove(entity e) {
            return store_.remove<C>(e);
        }

        template< typename C >
        bool has(entity e) {
            return store_.has<C>(e);
        }
        
        typedef boost::container::flat_set<entity> active_entity_list;
        
        const active_entity_list& active_entities() const {
            return active_entities_;
        }

    private:
        Store store_;
        active_entity_list active_entities_;
        std::vector<entity> recyclable_entities_;
    };

    template<typename... Components>
    class default_world : public world< array_of_struct::store<Components...> > {
    };
}