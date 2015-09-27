#pragma once

#include "node.h"

namespace scenimp {

    typedef boost::container::flat_set< std::shared_ptr< node > > node_set;

    class scene;
    class rendering;

    class group : public node {
    public:
        group();
        group(const group&) = delete;
        virtual ~group();

        const node_set& children() const;
        void add_child(std::shared_ptr< node > node);
        void remove_child(std::shared_ptr< node > node);

    protected:
        virtual void do_render(rendering& r);

    private:
        node_set children_;
    };

}


