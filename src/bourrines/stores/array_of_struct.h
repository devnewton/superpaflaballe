#pragma once

#include "../entity.h"

#include <type_traits>
#include <boost/optional.hpp>
#include <boost/intrusive/list.hpp>

namespace bourrines {

    namespace array_of_struct {

        struct active_entities_tag;

        typedef boost::intrusive::list_base_hook< boost::intrusive::tag<active_entities_tag> > active_entities_hook;

        template<typename... Components>
        class component_struct : public active_entities_hook {
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
                active_entities_.push_back(entities_components_[e]);
                return e;
            }

            void kill_entity(entity e) {
                active_entities_.erase(active_entities_.iterator_to(entities_components_[e]));
                recyclable_entities_.push_back(e);
            }

            entity recycle_entity() {
                if (!recyclable_entities_.empty()) {
                    entity e = recyclable_entities_.back();
                    recyclable_entities_.pop_back();
                    entities_components_[e] = ComponentContainer();
                    active_entities_.push_back(entities_components_[e]);
                    return e;
                } else {
                    return null_entity;
                }
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
            typedef boost::intrusive::list< ComponentContainer, boost::intrusive::base_hook<active_entities_hook> > active_entities_list;

            std::vector<ComponentContainer> entities_components_;
            active_entities_list active_entities_;
            std::vector<entity> recyclable_entities_;
        };
    }

}