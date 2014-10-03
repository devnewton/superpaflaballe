#pragma once

#include <type_traits>
#include <boost/optional.hpp>
#include <boost/dynamic_bitset.hpp>

#include "../entity.h"

namespace bourrines {

    template<typename... Components>
    class struct_of_array_store_base {
    protected:

        template<typename F>
        void for_each(F) {
        }
    };

    template< typename Component, typename... Components >
    class struct_of_array_store_base< Component, Components... > : private struct_of_array_store_base< Components... > {
    public:

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, C& >::type get(entity e) {
            return *components_[e];
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), C& >::type get(entity e) {
            return struct_of_array_store_base < Components...>::template get<C>(e);
        }

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, const C& >::type get(entity e) const {
            return *components_[e];
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), const C& >::type get(entity e) const {
            return struct_of_array_store_base < Components...>::template get<C>(e);
        }

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, C& >::type add(entity e) {
            components_[e] = C();
            return *components_[e];
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), C& >::type add(entity e) {
            return struct_of_array_store_base < Components...>::template add<C>(e);
        }

        template< typename C >
        typename std::enable_if< std::is_same< C, Component >::value, void >::type remove(entity e) {
            components_[e] = boost::none;
        }

        template< typename C >
        typename std::enable_if< !(std::is_same< C, Component >::value), void >::type remove(entity e) {
            struct_of_array_store_base < Components...>::template remove<C>(e);
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
            return struct_of_array_store_base < Components...>::template has<C>(e);
        }

        typedef std::vector<boost::optional<Component>> component_vector;
        
        component_vector& get_components() {
            return components_;
        }

    protected:

        template<typename F>
        void for_each(F fun) {
            fun(this);
            struct_of_array_store_base < Components...>::for_each(fun);
        }

        component_vector components_;
    };

    template<typename... Components>
    class struct_of_array_store : public struct_of_array_store_base<Components...> {
    public:

        entity create_entity() {
            entities_.push_back(1);
            resize_components(entities_.size());
            return entities_.size() - 1;
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

        boost::dynamic_bitset<> entities_;
    };

}