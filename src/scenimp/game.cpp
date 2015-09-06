#include "game.h"
#include "sdl_exception.h"

#include <SDL.h>

namespace scenimp {

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
        assets_ = new scenimp::assets(*this);
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

    std::shared_ptr< SDL_Texture > game::create_text_texture(std::shared_ptr< TTF_Font > font, const std::string& str, const SDL_Color& color) {
        std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *) > text_surface(TTF_RenderText_Blended(font.get(), str.c_str(), color), SDL_FreeSurface);
        return std::shared_ptr< SDL_Texture >(SDL_CreateTextureFromSurface(renderer(), text_surface.get()), SDL_DestroyTexture);
    }

}
