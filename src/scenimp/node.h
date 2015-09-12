#pragma once

#include "transform.h"
#include <boost/container/flat_set.hpp>

namespace scenimp {

    class group;
    class scene;
    class rendering;

    class node {
    public:
        node();
        node(const node&) = delete;
        virtual ~node();

        virtual void render(rendering& r) = 0;

        transform& local_transform();
        const transform& local_transform() const;

    private:
        class transform local_transform_;
        group* parent_;

        friend class scene;
    };

    typedef boost::container::flat_set<node* > node_list;

}


