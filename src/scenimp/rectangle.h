#pragma once

#include "shape_base.h"

namespace scenimp {

    class rectangle : public shape_base {
    public:
        rectangle();
        rectangle(const rectangle& orig) = delete;
        virtual ~rectangle();

        bool filled() const;
        void set_filled(bool f);
        
        int width() const;
        void set_width(int w);

        int height() const;
        void set_height(int h);

    protected:
        virtual void do_render(rendering& r) override;

    private:
        int width_;
        int height_;
        bool filled_;
    };

}


