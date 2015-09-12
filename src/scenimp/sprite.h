#pragma once

#include "node.h"
#include "nanim.h"

namespace scenimp {

    class sprite : public node {
    public:
        sprite();
        sprite(const sprite& orig) = delete;
        virtual ~sprite();
        
        virtual void render(rendering& r);
        
        std::shared_ptr< nanim::play > play();
        void set_play(std::shared_ptr< nanim::play > play);
    private:
        std::shared_ptr< nanim::play > play_;
    };

}


