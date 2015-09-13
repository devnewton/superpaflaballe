#pragma once

#include "group.h"
#include "sprite.h"
#include <boost/pool/object_pool.hpp>
#include <SDL.h>

namespace scenimp {

    class scene {
    public:
        scene(SDL_Renderer* r);
        scene(const scene&) = delete;
        ~scene();
        
        group& new_group(group* parent = nullptr);
        sprite& new_sprite(group* parent = nullptr);
        
        void delete_sprite(sprite* s);
        void delete_group(group* g);
        
        void render();

    private:
        void attach(node* child, group* parent);
        void detach(node* child);
        boost::object_pool<group> group_pool_;
        boost::object_pool<sprite> sprite_pool_;
        group* root_;
        SDL_Renderer* renderer_;
    };

}

