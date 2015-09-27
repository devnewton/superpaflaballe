#pragma once

#include "node.h"
#include <SDL_pixels.h>
#include <boost/algorithm/clamp.hpp>

namespace scenimp {

    class progressbar : public node {
    public:
        progressbar();
        progressbar(const progressbar& orig) = delete;
        virtual ~progressbar();

        int width() const;
        void set_width(int w);

        int height() const;
        void set_height(int h);
        
        int progress();
        void set_progress(int p);
        
        int maximum() const;
        void set_maximum(int m);

    protected:
        virtual void do_render(rendering& r) override;

    private:
        int width_;
        int height_;
        int progress_;
        int maximum_;
        SDL_Color background_color_;
        SDL_Color border_color_;
        SDL_Color progress_color_;
    };

}


