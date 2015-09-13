#include "group.h"
#include "rendering.h"

namespace scenimp {

    group::group() {
    }

    group::~group() {
    }

    const node_list& group::children() const {
        return children_;
    }

    void group::do_render(rendering& r) {
        for (auto& c : children_) {
            c->render(r);
        }
    }

}
