#pragma once

#include "assets.h"

namespace superpaflaballe {

    const int logical_screen_width = 1920;
    const int logical_screen_height = 1080;

    class game {
    public:
        game();
        ~game();

        SDL_Window* window();
        SDL_Renderer* renderer();
        superpaflaballe::assets& assets();

        std::shared_ptr< SDL_Texture > create_text_texture(std::shared_ptr< TTF_Font > font, const std::string& str, const SDL_Color& color = {255, 255, 255, 0});

    private:
        superpaflaballe::assets* assets_;
        SDL_Window* window_;
        SDL_Renderer* renderer_;
    };

}

