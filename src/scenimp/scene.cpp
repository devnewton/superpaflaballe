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

    std::shared_ptr<group> scene::new_group(std::shared_ptr<group> parent) {
        auto g = std::make_shared<group>();
        if (!parent) {
            parent = root_;
        }
        parent->add_child(g);
        return g;
    }

    std::shared_ptr<sprite> scene::new_sprite(std::shared_ptr<group> parent) {
        auto s = std::make_shared<sprite>();
        if (!parent) {
            parent = root_;
        }
        parent->add_child(s);
        return s;
    }
    
    std::shared_ptr<label> scene::new_label(std::shared_ptr<group> parent) {
        auto l = std::make_shared<label>();
        if (!parent) {
            parent = root_;
        }
        parent->add_child(l);
        return l;
    }

    void scene::render() {
        rendering r(renderer_);
        root_->render(r);
    }

}
