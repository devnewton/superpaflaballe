#pragma once

#include "node.h"
#include "rendering.h"
#include <SDL_ttf.h>

namespace scenimp {

    class label : public node {
    public:
        label();
        label(const label& orig) = delete;
        virtual ~label();

        const std::string& text() const;
        void set_text(const std::string& t);

        std::shared_ptr< TTF_Font > font();
        void set_font(std::shared_ptr< TTF_Font > font);

        const SDL_Color& color() const;
        void set_color(const SDL_Color& color);

        SDL_RendererFlip flip() const;
        void set_flip(SDL_RendererFlip flip);

        double angle()const;
        void set_angle(double a);

        void set_fixed_size(int w, int h);
        void set_dynamic_size();

    protected:
        virtual void do_render(rendering& r) override;

    private:
        void set_dirty();
        void update(rendering& r);

        std::string text_;
        SDL_Color color_;
        std::shared_ptr< TTF_Font > font_;
        std::shared_ptr< SDL_Texture > texture_;
        double angle_;
        int width_;
        int height_;
        SDL_RendererFlip flip_;

    };

}


