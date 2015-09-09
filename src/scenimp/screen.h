#pragma once

#include "assets.h"

namespace scenimp {

    class screen {
    public:
        screen();
        ~screen();

        int logical_screen_width() const;
        int logical_screen_height() const;

        SDL_Renderer* renderer();
        scenimp::assets& assets();

        std::shared_ptr< SDL_Texture > create_text_texture(std::shared_ptr< TTF_Font > font, const std::string& str, const SDL_Color& color = {255, 255, 255, 0});

    private:
        scenimp::assets* assets_;
        SDL_Window* window_;
        SDL_Renderer* renderer_;
    };

}

