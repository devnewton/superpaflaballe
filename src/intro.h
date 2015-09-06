#pragma once

#include "scenimp/game.h"
#include "scenimp/nanim.h"
#include "scenimp/assets.h"

namespace superpaflaballe {

    class intro {
    public:
        intro(scenimp::game& g);
        ~intro();
        void tick();
        bool is_finished();
    private:
        scenimp::game& game_;
        std::shared_ptr<scenimp::nanim::play> play_;
        std::shared_ptr<Mix_Music> music_;
    };

}

