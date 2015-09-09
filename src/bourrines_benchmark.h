#pragma once

#include "scenimp/screen.h"
#include "scenimp/nanim.h"
#include "scenimp/assets.h"
#include "bourrines/bourrines.h"

#include <boost/timer/timer.hpp>

namespace superpaflaballe {

    struct pos_component {
        int x_, y_;
    };

    struct dir_component {
        int dx_, dy_;
    };
    
    struct life_component {
        int life_;
    };

    struct anim_component {
        std::shared_ptr< scenimp::nanim::play > play_;
    };

    typedef bourrines::default_world<pos_component, dir_component, life_component, anim_component> world;

    class bourrines_benchmark {
    public:
        bourrines_benchmark(scenimp::screen& g, int num_entity, int num_ticks);
        ~bourrines_benchmark();
        
        void tick();
        
        bool is_finished();
        void create_ned();
        
    private:
        world world_;
        scenimp::screen& screen_;
        std::shared_ptr< scenimp::nanim::collection > ned_anim_;
        boost::timer::auto_cpu_timer timer_;
        int remaining_ticks_;
    };

}

