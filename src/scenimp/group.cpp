#include "group.h"

namespace scenimp {

    group::group() {
    }

    group::~group() {
    }

    const node_list& group::children() const {
        return children_;
    }
    
    void group::render(rendering& r) {
        for(auto& c : children_) {
            c->render(r);
        }
    }

}
