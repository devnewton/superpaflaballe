#pragma once

#include <SDL_rect.h>
#include <memory>

namespace scenimp {

    class group;
    class scene;
    class rendering;

    class node : public std::enable_shared_from_this<node> {
    public:
        node();
        node(const node&) = delete;
        virtual ~node();
        
        void remove_from_parent();
        
        void render(rendering& r);

        const SDL_Point& pos() const;
        SDL_Point& pos();

    protected:
        virtual void do_render(rendering& r) = 0;

    private:
        SDL_Point pos_;
        std::weak_ptr<group> parent_;

        friend class group;
    };

}


