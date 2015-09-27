#include "scene.h"
#include "rendering.h"
#include <iostream>
#include <exception>

namespace scenimp {

    scene::scene(SDL_Renderer* r)
    : root_(std::make_shared<group>())
    , renderer_(r) {
    }

    scene::~scene() {
    }

    void scene::render() {
        rendering r(renderer_);
        root_->render(r);
    }

}
