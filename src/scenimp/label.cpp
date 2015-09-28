#include "label.h"
#include "rendering.h"

namespace scenimp {

    namespace {
        const SDL_Color defaultLabelColor = {255, 255, 255, 0};
    }

    label::label()
    : color_(defaultLabelColor)
    , angle_(0.0)
    , width_(-1)
    , height_(-1)
    , flip_(SDL_FLIP_NONE) {
    }

    label::~label() {
    }

    void label::do_render(rendering& r) {
        if (font_ && !text_.empty()) {
            const SDL_Point& pos = r.current_pos();
            update(r);
            SDL_Rect rect_ = {pos.x + -width_ / 2, pos.y + -height_ / 2, width_, height_};
            SDL_RenderCopyEx(r.renderer(), texture_.get(), NULL, &rect_, angle_, NULL, flip_);
        }
    }

    const std::string& label::text() const {
        return text_;
    }

    void label::set_text(const std::string& t) {
        text_ = t;
        set_dirty();
    }

    std::shared_ptr< TTF_Font > label::font() {
        return font_;
    }

    void label::set_font(std::shared_ptr< TTF_Font > font) {
        font_ = font;
        set_dirty();
    }

    const SDL_Color& label::color() const {
        return color_;
    }

    void label::set_color(const SDL_Color& color) {
        color_ = color;
        set_dirty();
    }

    void label::set_dirty() {
        texture_.reset();
    }

    void label::update(rendering& r) {
        if (!texture_) {
            std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *) > text_surface(TTF_RenderText_Blended(font_.get(), text_.c_str(), color_), SDL_FreeSurface);
            texture_ = std::shared_ptr< SDL_Texture >(SDL_CreateTextureFromSurface(r.renderer(), text_surface.get()), SDL_DestroyTexture);
        }
        if (texture_ && (width_ < 0 || height_ < 0)) {
            SDL_QueryTexture(texture_.get(),
                    NULL,
                    NULL,
                    &width_,
                    &height_);
        }
    }

    SDL_RendererFlip label::flip() const {
        return flip_;
    }

    void label::set_flip(SDL_RendererFlip flip) {
        flip_ = flip;
    }

    double label::angle()const {
        return angle_;
    }

    void label::set_angle(double a) {
        angle_ = a;
    }

    void label::set_fixed_size(int w, int h) {
        width_ = w;
        height_ = h;
    }

    void label::set_dynamic_size() {
        width_ = -1;
        height_ = -1;
    }

}
