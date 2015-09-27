#include "progressbar.h"
#include "rendering.h"

namespace scenimp {

    progressbar::progressbar()
    : width_(32)
    , height_(8)
    , progress_(100)
    , maximum_(100)
    , background_color_({255, 204, 0, 255})
    , border_color_({255, 255, 255, 255})
    , progress_color_({255, 0, 0, 255}) {
    }

    progressbar::~progressbar() {
    }

    void progressbar::do_render(rendering& r) {
        const point& pos = r.current_pos();

        SDL_Rect rect = {pos.x() + -width_ / 2, pos.y() + -height_ / 2, width_, height_};
        SDL_SetRenderDrawColor(r.renderer(), background_color_.r, background_color_.g, background_color_.b, background_color_.a);
        SDL_RenderFillRect(r.renderer(), &rect);

        SDL_Rect rect_ = {pos.x() + -width_ / 2, pos.y() + -height_ / 2, (progress_ * width_) / maximum_, height_};
        SDL_SetRenderDrawColor(r.renderer(), progress_color_.r, progress_color_.g, progress_color_.b, progress_color_.a);
        SDL_RenderFillRect(r.renderer(), &rect_);

        SDL_SetRenderDrawColor(r.renderer(), border_color_.r, border_color_.g, border_color_.b, border_color_.a);
        SDL_RenderDrawRect(r.renderer(), &rect);
        SDL_SetRenderDrawColor(r.renderer(), 0, 0, 0, 255);
    }

    int progressbar::width() const {
        return width_;
    }

    void progressbar::set_width(int w) {
        width_ = w;
    }

    int progressbar::height() const {
        return height_;
    }

    void progressbar::set_height(int h) {
        height_ = h;
    }

    int progressbar::progress() {
        return progress_;
    }

    void progressbar::set_progress(int p) {
        progress_ = boost::algorithm::clamp(p, 0, maximum_);
    }

    int progressbar::maximum() const {
        return maximum_;
    }

    void progressbar::set_maximum(int m) {
        maximum_ = std::max(m, 1);
        progress_ = boost::algorithm::clamp(progress_, 0, maximum_);
    }

}
