#include "node.h"
#include "group.h"
#include "rendering.h"

namespace scenimp {

    node::node()
    : pos_({0, 0}) {
    }

    node::~node() {
    }
    
    void node::remove_from_parent() {
        if(auto parent = parent_.lock()) {
            parent->remove_child(shared_from_this());
        }
    }

    const SDL_Point& node::pos() const {
        return pos_;
    }

    SDL_Point& node::pos() {
        return pos_;
    }

    void node::render(rendering& r) {
        r.push_pos(*this);
        do_render(r);
        r.pop_pos(*this);
    }

}
