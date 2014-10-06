#pragma once

#include "entity.h"

#include <boost/container/flat_set.hpp>

namespace bourrines {

    template<typename World>
    class system {
    public:

        virtual void created(entity e) {
        };

        virtual void killed(entity e) {
        };

        virtual void changed(entity e) {
        };

        virtual void process() {
        }

        void set_world(World& world) {
            world_ = world;
        }

    protected:
        World& world_;
    };

    template<typename World>
    class processing_system : public system<World> {
    public:

        virtual void process() {
            for (entity e : this->world_.active_entities()) {
                process(e);
            }
        }

        virtual void process(entity e) = 0;
    };

    template<typename World>
    class selective_processing_system : public system<World> {
    public:
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