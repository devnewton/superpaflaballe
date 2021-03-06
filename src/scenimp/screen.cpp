#include "screen.h"
#include "sdl_exception.h"

#include <SDL.h>

namespace scenimp {

    screen::screen() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            throw sdl_exception();
        }
        window_ = SDL_CreateWindow("superpaflaballe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_RESIZABLE);
        if (!window_) {
            SDL_Quit();
            throw sdl_exception();
        }
        renderer_ = SDL_CreateRenderer(window_, -1, 0/*SDL_RENDERER_SOFTWARE*/);
        if (!renderer_) {
            SDL_DestroyWindow(window_);
            SDL_Quit();
            throw sdl_exception();
        }
        SDL_RenderSetLogicalSize(renderer_, 1920, 1080);
        assets_ = new scenimp::assets(renderer_);
    }

    screen::~screen() {
        delete assets_;
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    int screen::logical_screen_width() const {
        int w, h;
        SDL_RenderGetLogicalSize(renderer_, &w, &h);
        return w;
    }

    int screen::logical_screen_height() const {
        int w, h;
        SDL_RenderGetLogicalSize(renderer_, &w, &h);
        return h;
    }

    SDL_Renderer* screen::renderer() {
        return renderer_;
    }

    assets& screen::assets() {
        return *assets_;
    }

}
