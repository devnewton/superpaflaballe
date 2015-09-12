#include "node.h"
#include "group.h"

namespace scenimp {

    node::node()
    : parent_(nullptr) {
    }

    node::~node() {
    }

    transform& node::local_transform() {
        return local_transform_;
    }

    const transform& node::local_transform() const {
        return local_transform_;
    }
}
