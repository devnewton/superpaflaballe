#include "assets.h"
#include "game.h"
#include "framerate.h"
#include "sdl_exception.h"
#include "bourrines_benchmark.h"
#include <SDL.h>
#include <iostream>
#include <string>

int main(int, char**) {
    try {
        superpaflaballe::game game;
        superpaflaballe::framerate framerate;

        superpaflaballe::bourrines_benchmark benchmark(game, 10000, 60 * 10);
        SDL_Event event;
        for (;;) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }
            }
            if(benchmark.is_finished()) {
                return 0;
            }
            SDL_RenderClear(game.renderer());
            benchmark.tick();
            SDL_RenderPresent(game.renderer());
            framerate.limit();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error " << e.what() << std::endl;
    }
}
