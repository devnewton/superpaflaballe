#pragma once

#include "game.h"
#include "nanim.h"
#include "assets.h"

namespace superpaflaballe {

    class intro {
    public:
        intro(game& g);
        void tick();
        bool is_finished();
    private:
        game& game_;
        std::shared_ptr<superpaflaballe::nanim::play> play_;
    };

}

