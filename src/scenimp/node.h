#pragma once

#include "geometry.h"

namespace scenimp {

    class group;
    class scene;
    class rendering;

    class node : public std::enable_shared_from_this<node> {
    public:
        node();
        node(const node&) = delete;
        virtual ~node();
        
        void remove();
        
        void render(rendering& r);

        const point& pos() const;
        point& pos();

    protected:
        virtual void do_render(rendering& r) = 0;

    private:
        point pos_;
        std::weak_ptr<group> parent_;

        friend class group;
    };

}


