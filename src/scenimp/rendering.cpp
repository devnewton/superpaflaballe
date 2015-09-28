#include <stack>

#include "rendering.h"
#include "node.h"

namespace scenimp {

    rendering::rendering(SDL_Renderer* r)
    : pos_({0, 0})
    , renderer_(r) {
    }

    rendering::~rendering() {
    }

    SDL_Renderer* rendering::renderer() {
        return renderer_;
    }

    void rendering::push_pos(const node& n) {
        const SDL_Point& node_pos = n.pos();
        pos_.x += node_pos.x;
        pos_.y += node_pos.y;
    }

    const SDL_Point& rendering::current_pos() const {
        return pos_;
    }

    void rendering::pop_pos(const node& n) {
        const SDL_Point& node_pos = n.pos();
        pos_.x -= node_pos.x;
        pos_.y -= node_pos.y;
    }
}
