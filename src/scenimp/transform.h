#pragma once

namespace scenimp {

    class transform {
    public:
        transform();
        void translate(int x, int y);

        void combine_with(const transform& other);

    private:
        int tx_, ty_;

    };

}


