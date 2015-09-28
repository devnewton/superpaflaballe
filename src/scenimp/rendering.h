#pragma once

#include <SDL.h>

namespace scenimp {
    class node;

    class rendering {
    public:
        rendering(SDL_Renderer* r);
        rendering(const rendering&) = delete;
        ~rendering();

        void push_pos(const node& n);
        const SDL_Point& current_pos() const;
        void pop_pos(const node& n);
        
        SDL_Renderer* renderer();

    private:
        SDL_Point pos_;
        SDL_Renderer* renderer_;
    };

}


