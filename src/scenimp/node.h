#pragma once

#include "geometry.h"

namespace scenimp {

    class group;
    class scene;
    class rendering;

    class node {
    public:
        node();
        node(const node&) = delete;
        virtual ~node();

        void render(rendering& r);

        const point& pos() const;
        point& pos();

    protected:
        virtual void do_render(rendering& r) = 0;

    private:
        point pos_;
        group* parent_;

        friend class scene;
        friend class group;
    };

}


