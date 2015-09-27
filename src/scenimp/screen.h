#pragma once

#include "assets.h"

namespace scenimp {

    class screen {
    public:
        screen();
        screen(const screen&) = delete;
        ~screen();

        int logical_screen_width() const;
        int logical_screen_height() const;

        SDL_Renderer* renderer();
        scenimp::assets& assets();

    private:
        scenimp::assets* assets_;
        SDL_Window* window_;
        SDL_Renderer* renderer_;
    };

}

