#include "sprite.h"
#include "rendering.h"

namespace scenimp {

    sprite::sprite()
    : angle_(0.0)
    , width_(32)
    , height_(32)
    , flip_(SDL_FLIP_NONE) {
    }

    sprite::~sprite() {
    }

    void sprite::do_render(rendering& r) {
        const SDL_Point& pos = r.current_pos();
        SDL_Rect rect = {pos.x + -width_ / 2, pos.y + -height_ / 2, width_, height_};
        SDL_RenderCopyEx(r.renderer(), play_->current_frame().image().get(), &play_->current_frame().rect(), &rect, angle_, NULL, flip_);
    }

    std::shared_ptr< nanim::play > sprite::play() {
        return play_;
    }

    void sprite::set_play(std::shared_ptr< nanim::play > play) {
        play_ = play;
    }

    SDL_RendererFlip sprite::flip() const {
        return flip_;
    }

    void sprite::set_flip(SDL_RendererFlip flip) {
        flip_ = flip;
    }

    double sprite::angle()const {
        return angle_;
    }

    void sprite::set_angle(double a) {
        angle_ = a;
    }

    int sprite::width() const {
        return width_;
    }

    void sprite::set_width(int w) {
        width_ = w;
    }

    int sprite::height() const {
        return height_;
    }

    void sprite::set_height(int h) {
        height_ = h;
    }
}
