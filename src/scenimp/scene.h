#pragma once

#include "label.h"
#include "group.h"
#include "sprite.h"
#include <SDL.h>

namespace scenimp {

    class scene {
    public:
        scene(SDL_Renderer* r);
        scene(const scene&) = delete;
        ~scene();
        
        std::shared_ptr< group > new_group(std::shared_ptr< group > parent = nullptr);
        std::shared_ptr< sprite > new_sprite(std::shared_ptr< group > parent = nullptr);
        std::shared_ptr< label > new_label(std::shared_ptr< group > parent = nullptr);

        void render();

    private:
        std::shared_ptr<group> root_;
        SDL_Renderer* renderer_;
    };

}

