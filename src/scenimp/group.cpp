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
        for (auto& n : children_) {
            n->render(r);
        }
    }
    void group::add_child(std::shared_ptr< node > node) {
        if(node->parent_.lock()) {
            throw new std::runtime_error("node is already in a group");
        }
        node->parent_ = std::static_pointer_cast<group>( shared_from_this() );
        children_.insert(node);
    }
    void group::remove_child(std::shared_ptr< node > node) {
        if(node->parent_.lock() != shared_from_this()) {
            throw new std::runtime_error("cannot remove a node that does not belong to this group");
        }
        children_.erase(node);
    }
}
