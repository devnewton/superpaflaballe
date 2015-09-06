#include "group.h"

namespace scenimp {

    group::group() {
    }

    group::~group() {
    }

    void group::attach(std::shared_ptr<node> node) {
        node->parent_ = std::static_pointer_cast<group>(shared_from_this());
        children_.insert(node);
    }

    void group::detach(std::shared_ptr<node> node) {
        node->parent_.reset();
        children_.erase(node);
    }

    const node_list& group::children() const {
        return children_;
    }

}
