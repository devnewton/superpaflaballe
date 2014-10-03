#pragma once

#include <type_traits>
#include "../entity.h"

namespace bourrines {

    template<typename... Components>
    class component_struct {
    };

    template< typename Component, typename... Components >
    class component_struct< Component, Components... > : private component_struct< Components... > {
    public:

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, C& >::type get() {
            return component_;
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), C& >::type get() {
            return component_struct < Components...>::template get<C>();
        }

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, const C& >::type get() const {
            return component_;
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), const C& >::type get() const {
            return component_struct < Components...>::template get<C>();
        }

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, C& >::type add() {
            is_active_ = true;
            return component_;
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), C& >::type add() {
            return component_struct < Components...>::template add<C>();
        }

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, void >::type remove() {
            is_active_ = false;
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), void >::type remove() {
            component_struct < Components...>::template remove<C>();
        }

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, bool >::type has() const {
            return is_active_;
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), bool >::type has() {
            return component_struct < Components...>::template has<C>();
        }

    private:
        Component component_;
        bool is_active_;
    };

    template<typename... Components>
    class array_of_struct_store {
    public:

        entity create_entity() {
            entities_components_.push_back(ComponentContainer());
            return entities_components_.size() - 1;
        }

        void kill_entity(entity e) {
            entities_components_[e] = ComponentContainer();
        }

        entity recycle_entity() {
            //TODO
            return null_entity;
        }

        template< typename C >
        C& get(entity e) {
            return entities_components_[e].get<C>();
        }

        template< typename C >
        const C& get(entity e) const {
            return entities_components_[e].get<C>();
        }

        template< typename C >
        C& add(entity e) {
            return entities_components_[e].add<C>();
        }

        template< typename C >
        void remove(entity e) {
            return entities_components_[e].remove<C>();
        }

        template< typename C >
        bool has(entity e) {
            return entities_components_[e].has<C>();
        }

    private:
        typedef component_struct < Components...> ComponentContainer;
        std::vector<ComponentContainer> entities_components_;
    };

}