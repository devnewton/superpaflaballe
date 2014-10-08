#include <bits/unique_ptr.h>

#include "bourrines_benchmark.h"
#include "bourrines/world.h"

#include <memory>

namespace superpaflaballe {

    class move_system : public bourrines::selective_processing_system<world> {
    public:

        virtual bool accept(bourrines::entity e) {
            return has<pos_component>(e) && has<dir_component>(e);
        }

        virtual void process(bourrines::entity e) override {
            pos_component& pos = get<pos_component>(e);
            dir_component& dir = get<dir_component>(e);

            pos.x_ += dir.dx_;
            pos.y_ += dir.dy_;

            if (pos.x_ < 0) {
                dir.dx_ = -dir.dx_;
            }

            if (pos.y_ < 0) {
                dir.dy_ = -dir.dy_;
            }

            if (pos.x_ >= logical_screen_width) {
                dir.dx_ = -dir.dx_;
            }

            if (pos.y_ >= logical_screen_height) {
                dir.dy_ = -dir.dy_;
            }
        }

    };

    class render_system : public bourrines::selective_processing_system<world> {
    public:

        render_system(game& g)
        : game_(g) {
        }

        virtual bool accept(bourrines::entity e) {
            return has<pos_component>(e) && has<anim_component>(e);
        }

        virtual void process(bourrines::entity e) override {
            const pos_component& pos = get<pos_component>(e);
            const anim_component& anim = get<anim_component>(e);
            SDL_Rect rect;
            rect.w = 32;
            rect.h = 32;
            rect.x = pos.x_;
            rect.y = pos.y_;
            SDL_RenderCopy(game_.renderer(), anim.play_->current_frame().image().get(), &anim.play_->current_frame().rect(), &rect);
        }
    private:
        game& game_;
    };

    bourrines_benchmark::bourrines_benchmark(game& ga, assets& as, int num_entity, int num_ticks)
    : remaining_ticks_(num_ticks) {
        
        timer_.start();
        
        world_.add_system(0, new move_system());
        world_.add_system(1, new render_system(ga));
        auto ned_anim = as.animations("ned.json")->first();
        while (num_entity--) {
            bourrines::entity e = world_.create_entity();
            pos_component& pos = world_.add<pos_component>(e);
            pos.x_ = std::rand() % logical_screen_width;
            pos.y_ = std::rand() % logical_screen_height;

            dir_component& dir = world_.add<dir_component>(e);
            dir.dx_ = (1 + (std::rand() % 10)) * ((std::rand() % 1) ? -1 : 1);
            dir.dy_ = (1 + (std::rand() % 10)) * ((std::rand() % 1) ? -1 : 1);

            world_.add<anim_component>(e).play_ = std::make_shared<superpaflaballe::nanim::play>(ned_anim, superpaflaballe::nanim::loop);
            
            world_.changed(e);
        }
        
        timer_.stop();
        std::cout << "bourrines_benchmark init: " << timer_.format() << std::endl;
        timer_.start();
        timer_.stop();
    }
    
    bourrines_benchmark::~bourrines_benchmark() {
        std::cout << "bourrines_benchmark accumulated ticks: " << timer_.format() << std::endl;
    }
    
    void bourrines_benchmark::tick() {
        timer_.resume();
        world_.tick();
        timer_.stop();
        --remaining_ticks_;
    }
    
    bool bourrines_benchmark::is_finished() {
        return remaining_ticks_ <= 0;
    }
}
