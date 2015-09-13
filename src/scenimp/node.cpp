#include "node.h"
#include "group.h"
#include "rendering.h"

namespace scenimp {

    node::node()
    : pos_(0, 0)
    , parent_(nullptr) {
    }

    node::~node() {
    }

    const point& node::pos() const {
        return pos_;
    }

    point& node::pos() {
        return pos_;
    }

    void node::render(rendering& r) {
        r.push_pos(*this);
        do_render(r);
        r.pop_pos(*this);
    }

}
