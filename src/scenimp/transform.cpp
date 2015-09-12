#include "transform.h"

namespace scenimp {

    transform::transform()
    : tx_(0)
    , ty_(0) {
    }

    void transform::translate(int x, int y) {
        tx_ += x;
        ty_ += y;
    }

    void transform::combine_with(const transform& other) {
        tx_ += other.tx_;
        ty_ += other.ty_;
    }
}
