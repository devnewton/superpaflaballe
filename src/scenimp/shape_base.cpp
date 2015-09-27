#include "shape_base.h"

namespace scenimp {

    shape_base::shape_base() {
    }

    shape_base::~shape_base() {
    }

    void shape_base::prerender(rendering& r) {
        SDL_SetRenderDrawColor(r.renderer(), color_.r, color_.g, color_.b, color_.a);

    }

    void shape_base::postrender(rendering& r) {
        SDL_SetRenderDrawColor(r.renderer(), 0, 0, 0, 255);
    }

    SDL_Color shape_base::color() const {
        return color_;
    }

    void shape_base::set_color(SDL_Color c) {
        color_ = c;
    }

}