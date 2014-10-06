#pragma once

#include "stores/array_of_struct.h"
#include "stores/struct_of_array.h"

namespace bourrines {

    template<typename Store>
    class world {
    public:
        entity create_entity() {
            entity e = store_.recycle_entity();
            if (e == null_entity) {
                e = store_.create_entity();
            }
            return e;
        }

        void kill_entity(entity e) {
            store_.kill_entity(e);
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

    private:
        Store store_;
    };
    
    template<typename... Components>
    class default_world : public world< struct_of_array::store<Components...> > {
        
    };
}