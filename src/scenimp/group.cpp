#include "group.h"
#include "rendering.h"

namespace scenimp {

    group::group() {
    }

    group::~group() {
    }

    const node_set& group::children() const {
        return children_;
    }

    void group::do_render(rendering& r) {
        for (auto& c : children_.get<container::z_index>()) {
            c.node->render(r);
        }
    }

}
