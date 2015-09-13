#pragma once

#include "node.h"
#include "nanim.h"

namespace scenimp {

    class sprite : public node {
    public:
        sprite();
        sprite(const sprite& orig) = delete;
        virtual ~sprite();

        virtual void render(rendering& r);

        std::shared_ptr< nanim::play > play();
        void set_play(std::shared_ptr< nanim::play > play);

        SDL_RendererFlip flip() const;
        void set_flip(SDL_RendererFlip flip);

        double angle()const;
        void set_angle(double a);

        int width() const;
        void set_width(int w);

        int height() const;
        void set_height(int h);

    private:
        double angle_;
        int width_;
        int height_;
        SDL_RendererFlip flip_;
        std::shared_ptr< nanim::play > play_;
    };

}


