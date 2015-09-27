#pragma once

#include "node.h"
#include "rendering.h"

namespace scenimp {

    class shape_base : public node {
    public:
        shape_base();
        shape_base(const shape_base& orig) = delete;
        virtual ~shape_base();

        SDL_Color color() const;
        void set_color(SDL_Color c);
    protected:

        void prerender(rendering& r);
        void postrender(rendering& r);

    private:
        SDL_Color color_;
    };
}

