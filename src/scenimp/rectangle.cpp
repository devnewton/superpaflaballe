#include "rectangle.h"
#include "rendering.h"

namespace scenimp {

    rectangle::rectangle()
    : width_(32)
    , height_(32)
    , filled_(false) {
    }

    rectangle::~rectangle() {
    }

    void rectangle::do_render(rendering& r) {
        prerender(r);
        const point& pos = r.current_pos();
        SDL_Rect rect = {pos.x() + -width_ / 2, pos.y() + -height_ / 2, width_, height_};
        if (filled_) {
            SDL_RenderFillRect(r.renderer(), &rect);
        } else {
            SDL_RenderDrawRect(r.renderer(), &rect);
        }
        postrender(r);
    }

    int rectangle::width() const {
        return width_;
    }

    void rectangle::set_width(int w) {
        width_ = w;
    }

    int rectangle::height() const {
        return height_;
    }

    void rectangle::set_height(int h) {
        height_ = h;
    }
}
