#include "node.h"
#include "group.h"

namespace scenimp {

    node::node() {
    }

    node::~node() {
    }

    void node::detach() {
        if (auto lockedParent = parent_.lock()) {
            lockedParent->detach(shared_from_this());
        }
    }

}
