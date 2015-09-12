#include "sprite.h"

namespace scenimp {

    sprite::sprite() {
    }

    sprite::~sprite() {
    }

    void sprite::render(rendering& r) {
        //TODO
    }

    std::shared_ptr< nanim::play > sprite::play() {
        return play_;
    }

    void set_play(std::shared_ptr< nanim::play > play) {
        play_ = play;
    }

}
