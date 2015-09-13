#include "node.h"
#include "group.h"
#include "rendering.h"

namespace scenimp {

    node::node()
    : parent_(nullptr),
    z_(0) {
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

    int node::z() const {
        return z_;
    }
}
