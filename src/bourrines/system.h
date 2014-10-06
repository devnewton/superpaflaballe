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

        virtual void process(const active_entity_list& ) {
        }

        void set_world(World* world) {
            world_ = world;
        }

        const World& world() {
            return *world_;
        }

    protected:
        World* world_;
    };

    template<typename World>
    class processing_system : public system<World> {
    public:

        virtual void process(const active_entity_list& entities) {
            for (entity e : entities) {
                process(e);
            }
        }

        virtual void process(entity e) = 0;
    };

    template<typename World>
    class selective_processing_system : public system<World> {
    public:

        virtual void process(const active_entity_list&) {
            for (entity e : entities_) {
                process(e);
            }
        }

        virtual void process(entity e) = 0;

        virtual bool accept(entity e) = 0;

        virtual void created(entity e) {
            if (accept(e)) {
                entities_.insert(e);
            }
        };

        virtual void killed(entity e) {
            entities_.erase(e);
        };

        virtual void changed(entity e) {
            if (accept(e)) {
                entities_.insert(e);
            }
        };

    private:
        boost::container::flat_set<entity> entities_;
    };

}