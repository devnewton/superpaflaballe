#pragma once


#include "node.h"

namespace scenimp {

    class scene;
    class rendering;

    class group : public node {
    public:
        group();
        group(const group&) = delete;
        virtual ~group();

        const node_list& children() const;

    protected:
        virtual void do_render(rendering& r);

    private:
        node_list children_;

        friend class scene;
    };

}


