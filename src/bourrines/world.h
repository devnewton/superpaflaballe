#pragma once

#include "system.h"

#include "stores/array_of_struct.h"
#include "stores/struct_of_array.h"

#include <boost/ptr_container/ptr_map.hpp>

namespace bourrines {

    template<typename Store>
    class world {
    public:
        typedef class world<Store> this_type;
        typedef system<this_type> system_type;
        
        world()
        : delta_(1000.0f / 60.0f) {            
        }

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
            for (const auto& it : systems_) {
                it.second->created(e);
            }
            return e;
        }

        void kill_entity(entity e) {
            active_entities_.erase(e);
            recyclable_entities_.push_back(e);
            for (const auto& it : systems_) {
                it.second->killed(e);
            }
        }

        void changed(entity e) {
            for (const auto& it : systems_) {
                it.second->changed(e);
            }
        }
        
        void set_delta(float delta) {
            delta_ = delta_;
        }
        
        float delta() const {
            return delta_;
        }

        void tick() {
            for (const auto& it : systems_) {
                it.second->process(active_entities_);
            }
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

        template<typename S>
        void add_system(int priority, std::unique_ptr<system_type> s) {
            s->set_world(this);
            systems_[priority] = s;
        }

    private:

        Store store_;
        active_entity_list active_entities_;
        std::vector<entity> recyclable_entities_;
        boost::ptr_multimap<int, system_type> systems_;
        float delta_;
    };

    template<typename... Components>
    class default_world : public world< array_of_struct::store<Components...> > {
    };
}