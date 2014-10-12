#include "game.h"
#include "sdl_exception.h"

#include <SDL.h>

namespace superpaflaballe {

    game::game() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            throw sdl_exception();
        }
        window_ = SDL_CreateWindow("superpaflaballe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_RESIZABLE);
        if (!window_) {
            SDL_Quit();
            throw sdl_exception();
        }
        renderer_ = SDL_CreateRenderer(window_, -1, 0);
        if (!renderer_) {
            SDL_DestroyWindow(window_);
            SDL_Quit();
            throw sdl_exception();
        }
        SDL_RenderSetLogicalSize(renderer_, logical_screen_width, logical_screen_height);
        assets_ = new superpaflaballe::assets(*this);
    }

    game::~game() {
        delete assets_;
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    SDL_Window* game::window() {
        return window_;
    }

    SDL_Renderer* game::renderer() {
        return renderer_;
    }
    
    assets& game::assets() {
        return *assets_;
    }

}
