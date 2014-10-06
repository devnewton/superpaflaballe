#include "assets.h"
#include "game.h"
#include "framerate.h"
#include "sdl_exception.h"
#include "bourrines/bourrines.h"
#include <SDL.h>
#include <iostream>
#include <string>

struct Pos {
    int x_, y_;
};

struct Life {
    int life_;
};


void test_bourrines() {
    bourrines::default_world<Pos, Life> world;
    bourrines::entity entity = world.create_entity();

    if (!world.has<Pos>(entity) && !world.has<Life>(entity)) {
        std::cout << "entity is empty" << std::endl;
    }

    world.add<Pos>(entity);
    world.get<Pos>(entity).x_ = 12;
    world.get<Pos>(entity).y_ = 55;

    world.add<Life>(entity);
    world.get<Life>(entity).life_ = 100;

    if (world.has<Pos>(entity)) {
        const Pos& p = world.get<Pos>(entity);

        std::cout << "pp x=" << p.x_ << " y=" << p.y_ << std::endl;
    }

    if (world.has<Life>(entity)) {
        Life& l = world.get<Life>(entity);
        l.life_ -= 10;
        std::cout << "hurt: life=" << world.get<Life>(entity).life_ << std::endl;
    }

    world.remove<Pos>(entity);
    if (!world.has<Pos>(entity)) {
        std::cout << "entity has no pos" << std::endl;
    }
    
    world.kill_entity(entity);
    
    bourrines::entity newentity = world.create_entity();
    if (!world.has<Pos>(newentity) && !world.has<Life>(newentity)) {
         std::cout << "newentity is fresh" << std::endl;
    }
}

int main(int, char**) {
    try {

        test_bourrines();

        superpaflaballe::game game;
        superpaflaballe::assets assets(game);
        superpaflaballe::framerate framerate;

        auto intro = std::make_shared<superpaflaballe::nanim::play>(assets.animations("intro/devnewton.json")->first(), superpaflaballe::nanim::loop);
        SDL_Event event;
        for (;;) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }
            }
            SDL_RenderClear(game.renderer());
            intro->update(1000 / 60);
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
