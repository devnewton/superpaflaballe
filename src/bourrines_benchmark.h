#pragma once

#include "game.h"
#include "nanim.h"
#include "assets.h"
#include "bourrines/bourrines.h"

namespace superpaflaballe {

    struct pos_component {
        int x_, y_;
    };

    struct dir_component {
        int dx_, dy_;
    };

    struct anim_component {
        std::shared_ptr< nanim::play > play_;
    };

    typedef bourrines::default_world<pos_component, dir_component, anim_component> world;

    class bourrines_benchmark {
    public:
        bourrines_benchmark(game& g, assets& a, int num_entity);
        
        void tick();
    private:
        world world_;
    };

}

