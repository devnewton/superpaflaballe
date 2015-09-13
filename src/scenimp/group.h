#pragma once

#include "node.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

namespace scenimp {

    namespace container {
        using namespace boost::multi_index;

        struct node_in_group {
            node_in_group(class node* n, int z)
            : node(n)
            , z(z) {
            }

            class node* node;
            int z;
        };

        struct node_index {
        };

        struct z_index {
        };

        typedef multi_index_container<
        node_in_group,
        indexed_by<
        hashed_unique< tag<node_index>, member< node_in_group, node*, &node_in_group::node > >,
        ordered_non_unique< tag< z_index >, member< node_in_group, int, &node_in_group::z > >
        >
        > node_set;
    }

    using container::node_set;
    using container::node_in_group;

    class scene;
    class rendering;

    class group : public node {
    public:
        group();
        group(const group&) = delete;
        virtual ~group();

        const node_set& children() const;

    protected:
        virtual void do_render(rendering& r);

    private:
        node_set children_;

        friend class scene;
    };

}


