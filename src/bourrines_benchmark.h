#pragma once

#include "scenimp/screen.h"
#include "scenimp/scene.h"
#include "scenimp/nanim.h"
#include "scenimp/assets.h"
#include "bourrines/bourrines.h"

#include <boost/timer/timer.hpp>

namespace superpaflaballe {

    struct dir_component {
        int dx_, dy_;
    };
    
    struct life_component {
        int life_;
    };

    struct sprite_component {
        std::shared_ptr<scenimp::group> group_;
        std::shared_ptr<scenimp::sprite> sprite_;
        
        ~sprite_component() {
            if(group_) {
                group_->remove_from_parent();
            }
        }
    };

    typedef bourrines::default_world<dir_component, life_component, sprite_component> world;

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
        scenimp::scene scene_;
        std::shared_ptr< scenimp::nanim::collection > ned_anim_;
        std::shared_ptr< TTF_Font > ned_font_;
        boost::timer::auto_cpu_timer timer_;
        int remaining_ticks_;
    };

}

