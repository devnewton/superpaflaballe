#pragma once

#include "label.h"
#include "group.h"
#include "rectangle.h"
#include "sprite.h"
#include <SDL.h>

namespace scenimp {

    class scene {
    public:
        scene(SDL_Renderer* r);
        scene(const scene&) = delete;
        ~scene();

        std::shared_ptr< group > new_group(std::shared_ptr< group > parent = nullptr) {return new_node<group>(parent);}
        std::shared_ptr< rectangle > new_rectangle(std::shared_ptr< group > parent = nullptr) {return new_node<rectangle>(parent);}
        std::shared_ptr< sprite > new_sprite(std::shared_ptr< group > parent = nullptr) {return new_node<sprite>(parent);}
        std::shared_ptr< label > new_label(std::shared_ptr< group > parent = nullptr) {return new_node<label>(parent);}

        void render();

    private:

        template<class T>
        std::shared_ptr<T> new_node(std::shared_ptr< group> parent = nullptr) {
            auto n = std::make_shared<T>();
            if (!parent) {
                parent = root_;
            }
            parent->add_child(n);
            return n;
        }
        
        std::shared_ptr<group> root_;
        SDL_Renderer* renderer_;
    };

}

