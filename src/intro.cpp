#include <bits/unique_ptr.h>

#include "intro.h"
#include "bourrines/world.h"

#include <memory>

namespace superpaflaballe {

    intro::intro(game& ga, assets& ass)
    : game_(ga)
    , play_(std::make_shared<superpaflaballe::nanim::play>(ass.animations("intro/devnewton.json")->first(), superpaflaballe::nanim::loop)) {
    }

    void intro::tick() {
        play_->update(1000 / 60);
        SDL_Rect rect;
        rect.w = 512;
        rect.h = 116;
        rect.x = (superpaflaballe::logical_screen_width - rect.w) / 2;
        rect.y = (superpaflaballe::logical_screen_height - rect.h) / 2;
        SDL_RenderCopy(game_.renderer(), play_->current_frame().image().get(), &play_->current_frame().rect(), &rect);
    }
}
