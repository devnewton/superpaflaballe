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

        virtual void render(rendering& r);

        const node_list& children() const;

    private:
        node_list children_;
        
        friend class scene;
    };

}


