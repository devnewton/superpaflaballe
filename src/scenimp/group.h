#pragma once

#include "node.h"

namespace scenimp {

    class group : public node {
    public:
        group();
        group(const group& orig) = delete;
        virtual ~group();

        void attach(std::shared_ptr< node > node);
        void detach(std::shared_ptr< node > node);

        const node_list& children() const;

    private:
        node_list children_;
    };

}


