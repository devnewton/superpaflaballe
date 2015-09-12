#include <stack>

#include "rendering.h"

namespace scenimp {

    rendering::rendering() {
    }

    rendering::~rendering() {
    }

    void rendering::push_transform(const transform& t) {
        transform_stack_.push(t);
    }
    const transform& rendering::current_transform() const {
        return transform_stack_.top();
    }
    void rendering::pop_transform() {
        transform_stack_.pop();
    }
}
