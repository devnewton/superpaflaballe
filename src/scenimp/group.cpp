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
        for (auto& c : children_) {
            c->render(r);
        }
    }
    
    void group::set_z(node* child, int z) {
        auto it = children_.find(child);
        children_.modify(it, [z](node* n) { n->z_ = z; });
    }

}
