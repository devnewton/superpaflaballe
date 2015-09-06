#pragma once

#include "node.h"
#include "nanim.h"

namespace scenimp {

    class sprite : public node {
    public:
        sprite();
        sprite(const sprite& orig) = delete;
        virtual ~sprite();
    private:
        std::shared_ptr< nanim::play > play_;
    };

}


