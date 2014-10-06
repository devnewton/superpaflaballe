#pragma once

#include "../entity.h"

#include <type_traits>
#include <boost/optional.hpp>

namespace bourrines {

    namespace array_of_struct {

        template<typename... Components>
        class component_struct {
        };

        template< typename Component, typename... Components >
        class component_struct< Component, Components... > : public component_struct< Components... > {
        public:

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, C& >::type get() {
                return *component_;
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), C& >::type get() {
                return component_struct < Components...>::template get<C>();
            }

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, const C& >::type get() const {
                return *component_;
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), const C& >::type get() const {
                return component_struct < Components...>::template get<C>();
            }

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, C& >::type add() {
                component_ = C();
                return *component_;
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), C& >::type add() {
                return component_struct < Components...>::template add<C>();
            }

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, void >::type remove() {
                component_ = boost::none;
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), void >::type remove() {
                component_struct < Components...>::template remove<C>();
            }

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, bool >::type has() const {
                if (component_) {
                    return true;
                } else {
                    return false;
                }
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), bool >::type has() {
                return component_struct < Components...>::template has<C>();
            }

        private:
            boost::optional<Component> component_;
        };

        template<typename... Components>
        class store {
        public:

            entity create_entity() {
                entity e = entities_components_.size();
                entities_components_.push_back(ComponentContainer());
                return e;
            }

            void recycle_entity(entity e) {
                entities_components_[e] = ComponentContainer();
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

}