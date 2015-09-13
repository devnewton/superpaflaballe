#pragma once

#include "node.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/mem_fun.hpp>

namespace scenimp {

    namespace container {
        using namespace boost::multi_index;
        
        struct z_index {};

        typedef multi_index_container<
        node*,
        indexed_by<
            hashed_unique< identity< node* > >,
            ordered_non_unique< tag< z_index >, const_mem_fun<node, int, &node::z > >
        >
        > node_set;
    }
    
    using container::node_set;

    class scene;
    class rendering;

    class group : public node {
    public:
        group();
        group(const group&) = delete;
        virtual ~group();

        const node_set& children() const;
        void set_z(node* child, int z);

    protected:
        virtual void do_render(rendering& r);

    private:
        node_set children_;

        friend class scene;
    };

}


