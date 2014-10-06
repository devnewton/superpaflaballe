#pragma once

#include <type_traits>
#include <boost/optional.hpp>

#include "../entity.h"

namespace bourrines {

    namespace struct_of_array {

        template<typename... Components>
        class store_base {
        protected:

            template<typename F>
            void for_each(F) {
            }
        };

        template< typename Component, typename... Components >
        class store_base< Component, Components... > : private store_base< Components... > {
        public:

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, C& >::type get(entity e) {
                return *components_[e];
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), C& >::type get(entity e) {
                return store_base < Components...>::template get<C>(e);
            }

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, const C& >::type get(entity e) const {
                return *components_[e];
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), const C& >::type get(entity e) const {
                return store_base < Components...>::template get<C>(e);
            }

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, C& >::type add(entity e) {
                components_[e] = C();
                return *components_[e];
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), C& >::type add(entity e) {
                return store_base < Components...>::template add<C>(e);
            }

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, void >::type remove(entity e) {
                components_[e] = boost::none;
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), void >::type remove(entity e) {
                store_base < Components...>::template remove<C>(e);
            }

            template< typename C >
            typename std::enable_if< std::is_same< C, Component >::value, bool >::type has(entity e) const {
                if (components_[e]) {
                    return true;
                } else {
                    return false;
                }
            }

            template< typename C >
            typename std::enable_if< !(std::is_same< C, Component >::value), bool >::type has(entity e) {
                return store_base < Components...>::template has<C>(e);
            }

            typedef std::vector<boost::optional<Component>> component_vector;

            component_vector& get_components() {
                return components_;
            }

        protected:

            template<typename F>
            void for_each(F fun) {
                fun(this);
                store_base < Components...>::for_each(fun);
            }

            component_vector components_;
        };

        template<typename... Components>
        class store : public store_base<Components...> {
        public:

            store()
            : entities_components_size_(0) {
            }

            entity create_entity() {
                entity e = entities_components_size_++;
                resize_components(entities_components_size_);
                return e;
            }

            void recycle_entity(entity e) {
                remove_components_t remover(e);
                this->for_each(remover);
            }

        private:

            struct resize_components_t {

                resize_components_t(std::size_t s)
                : size_(s) {
                }

                std::size_t size_;

                template<typename ME>
                void operator()(ME me) {
                    me->get_components().resize(2);
                }
            };

            void resize_components(std::size_t s) {
                resize_components_t resizer(s);
                this->for_each(resizer);
            }

            struct remove_components_t {

                remove_components_t(entity e)
                : e_(e) {
                }

                entity e_;

                template<typename ME>
                void operator()(ME me) {
                    me->get_components()[e_] = boost::none;
                }
            };

            std::size_t entities_components_size_;
        };

    }

}