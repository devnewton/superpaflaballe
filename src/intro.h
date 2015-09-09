#pragma once

#include "scenimp/screen.h"
#include "scenimp/nanim.h"
#include "scenimp/assets.h"

namespace superpaflaballe {

    class intro {
    public:
        intro(scenimp::screen& g);
        ~intro();
        void tick();
        bool is_finished();
    private:
        scenimp::screen& screen_;
        std::shared_ptr<scenimp::nanim::play> play_;
        std::shared_ptr<Mix_Music> music_;
    };

}

