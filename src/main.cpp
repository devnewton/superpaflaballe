#include "assets.h"
#include "game.h"
#include "framerate.h"
#include "sdl_exception.h"
#include <iostream>
#include <string>
#include <SDL.h>

int main(int, char**) {
    try {
        superpaflaballe::game game;
        superpaflaballe::assets assets(game);
        superpaflaballe::framerate framerate;

        auto intro  = std::make_shared<superpaflaballe::nanim::play>(assets.animations("intro/devnewton.json")->first(), superpaflaballe::nanim::loop);
        SDL_Event event;
        for(;;) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }
            }
            SDL_RenderClear(game.renderer());
            intro->update(1000 / 60 );
            SDL_Rect rect;
            rect.w = 512;
            rect.h = 116;
            rect.x = (superpaflaballe::logical_screen_width - rect.w) / 2;
            rect.y = (superpaflaballe::logical_screen_height - rect.h) / 2;
            SDL_RenderCopy(game.renderer(), intro->current_frame().image().get(), &intro->current_frame().rect(), &rect);
            SDL_RenderPresent(game.renderer());
            framerate.limit();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error " << e.what() << std::endl;
    }
}
