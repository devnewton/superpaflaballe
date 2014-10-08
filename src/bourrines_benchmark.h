#pragma once

#include "game.h"
#include "nanim.h"
#include "assets.h"
#include "bourrines/bourrines.h"

#include <boost/timer/timer.hpp>

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
        bourrines_benchmark(game& g, assets& a, int num_entity, int num_ticks);
        ~bourrines_benchmark();
        
        void tick();
        
        bool is_finished();
    private:
        world world_;
        boost::timer::auto_cpu_timer timer_;
        int remaining_ticks_;
    };

}

