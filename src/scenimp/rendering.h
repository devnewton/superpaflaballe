#pragma once

#include "transform.h"
#include <stack>

namespace scenimp {

    class rendering {
    public:
        rendering();
        rendering(const rendering&) = delete;
        ~rendering();

        void push_transform(const transform& t);
        const transform& current_transform() const;
        void pop_transform();

    private:
        std::stack<transform> transform_stack_;
    };

}


