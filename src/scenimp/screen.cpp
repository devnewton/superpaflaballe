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
        renderer_ = SDL_CreateRenderer(window_, -1, 0);
        if (!renderer_) {
            SDL_DestroyWindow(window_);
            SDL_Quit();
            throw sdl_exception();
        }
        SDL_RenderSetLogicalSize(renderer_, 1920, 1080);
        assets_ = new scenimp::assets(*this);
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

    std::shared_ptr< SDL_Texture > screen::create_text_texture(std::shared_ptr< TTF_Font > font, const std::string& str, const SDL_Color& color) {
        std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *) > text_surface(TTF_RenderText_Blended(font.get(), str.c_str(), color), SDL_FreeSurface);
        return std::shared_ptr< SDL_Texture >(SDL_CreateTextureFromSurface(renderer(), text_surface.get()), SDL_DestroyTexture);
    }

}
