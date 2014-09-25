#ifndef superpaflaballe_sdl_h
#define superpaflaballe_sdl_h

#include <SDL.h>

namespace superpaflaballe {

    const int logical_screen_width = 1920;
    const int logical_screen_height = 1080;

    class game {
    public:
        game();
        ~game();

        SDL_Window* window();
        SDL_Renderer* renderer();

    private:
        SDL_Window* window_;
        SDL_Renderer* renderer_;
    };

}

#endif
