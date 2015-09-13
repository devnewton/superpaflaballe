#include <stack>

#include "rendering.h"
#include "node.h"

namespace scenimp {

    rendering::rendering(SDL_Renderer* r)
    : renderer_(r) {
    }

    rendering::~rendering() {
    }

    SDL_Renderer* rendering::renderer() {
        return renderer_;
    }

    void rendering::push_pos(const node& n) {
        const point& node_pos = n.pos();
        pos_.x(pos_.x() + node_pos.x());
        pos_.y(pos_.y() + node_pos.y());
    }

    const point& rendering::current_pos() const {
        return pos_;
    }

    void rendering::pop_pos(const node& n) {
        const point& node_pos = n.pos();
        pos_.x(pos_.x() - node_pos.x());
        pos_.y(pos_.y() - node_pos.y());
    }
}
