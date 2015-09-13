#pragma once

#include "entity.h"

#include <boost/container/flat_set.hpp>

namespace bourrines {

    template<typename World>
    class system {
    public:

        virtual void created(entity) {
        };

        virtual void killed(entity) {
        };

        virtual void changed(entity) {
        };

        virtual void process(const active_entity_list&) {
        }

        void set_world(World* world) {
            world_ = world;
        }

        const World& world() const {
            return *world_;
        }

        World& world() {
            return *world_;
        }

        template< typename C >
        C& get(entity e) {
            return world_->get<C>(e);
        }

        template< typename C >
        const C& get(entity e) const {
            return world_->get<C>(e);
        }

        template< typename C >
        C& add(entity e) {
            return world_->add<C>(e);
        }

        template< typename C >
        void remove(entity e) {
            return world_->remove<C>(e);
        }

        template< typename C >
        bool has(entity e) {
            return world_->has<C>(e);
        }

        template< typename C >
        bool has(entity e) const {
            return world_->has<C>(e);
        }

    private:
        World* world_;
    };
    
    template<typename World>
    class basic_system : public World::system_type {
    public:

        virtual void process(const active_entity_list&) override {
            process();
        }

        virtual void process() = 0;
    };

    template<typename World>
    class processing_system : public World::system_type {
    public:

        virtual void process(const active_entity_list& entities) override {
            for (entity e : entities) {
                process(e);
            }
        }

        virtual void process(entity e) = 0;
    };

    template<typename World>
    class selective_processing_system : public World::system_type {
    public:

        virtual void process(const active_entity_list&) override {
            for (entity e : entities_) {
                process(e);
            }
        }

        virtual void process(entity e) = 0;

        virtual bool accept(entity e) = 0;

        virtual void created(entity e) override {
            if (accept(e)) {
                entities_.insert(e);
            }
        };

        virtual void killed(entity e) override {
            entities_.erase(e);
        };

        virtual void changed(entity e) override {
            if (accept(e)) {
                entities_.insert(e);
            }
        };

    private:
        boost::container::flat_set<entity> entities_;
    };

}