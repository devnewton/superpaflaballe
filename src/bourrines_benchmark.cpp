#include <bits/unique_ptr.h>

#include "bourrines_benchmark.h"
#include "bourrines/world.h"

#include <memory>

namespace superpaflaballe {

    class hades_system : public bourrines::selective_processing_system<world> {
    public:

        virtual bool accept(bourrines::entity e) override {
            return has<life_component>(e);
        }

        virtual void process(bourrines::entity e) override {
            life_component& life = get<life_component>(e);

            if (life.life_-- < 0) {
                world().kill_entity(e);
            }
        }

    };

    class hera_system : public world::system_type {
    public:

        hera_system(bourrines_benchmark& benchmark, int num_ned_to_create)
        : benchmark_(benchmark)
        , num_ned_to_create_(num_ned_to_create) {
        }

        virtual void process(const bourrines::active_entity_list&) override {
            for (int i = 0; i < num_ned_to_create_; ++i) {
                benchmark_.create_ned();
            }
            num_ned_to_create_ = 0;
        }

        virtual void killed(bourrines::entity) override {
            ++num_ned_to_create_;
        };

    private:
        bourrines_benchmark& benchmark_;
        int num_ned_to_create_;

    };

    class move_system : public bourrines::selective_processing_system<world> {
    public:

        virtual bool accept(bourrines::entity e) override {
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

            if (pos.x_ >= scenimp::logical_screen_width) {
                dir.dx_ = -dir.dx_;
            }

            if (pos.y_ >= scenimp::logical_screen_height) {
                dir.dy_ = -dir.dy_;
            }
        }

    };

    class render_system : public bourrines::selective_processing_system<world> {
    public:

        render_system(scenimp::game& g)
        : game_(g) {
        }

        virtual bool accept(bourrines::entity e) override {
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
        scenimp::game& game_;
    };

    bourrines_benchmark::bourrines_benchmark(scenimp::game& ga, int num_entity, int num_ticks)
    : remaining_ticks_(num_ticks) {
        timer_.stop();
        ned_anim_ = ga.assets().animations("ned.json");
        world_.add_system(1, std::unique_ptr<hera_system>(new hera_system(*this, num_entity)));
        world_.add_system(2, std::unique_ptr<hades_system>(new hades_system()));
        world_.add_system(3, std::unique_ptr<move_system>(new move_system()));
        world_.add_system(4, std::unique_ptr<render_system>(new render_system(ga)));
    }

    bourrines_benchmark::~bourrines_benchmark() {
        std::cout << "bourrines_benchmark accumulated ticks: " << timer_.format() << std::endl;
    }

    void bourrines_benchmark::create_ned() {
        bourrines::entity e = world_.create_entity();
        pos_component& pos = world_.add<pos_component>(e);
        pos.x_ = std::rand() % scenimp::logical_screen_width;
        pos.y_ = std::rand() % scenimp::logical_screen_height;

        dir_component& dir = world_.add<dir_component>(e);
        dir.dx_ = (1 + (std::rand() % 10)) * ((std::rand() % 1) ? -1 : 1);
        dir.dy_ = (1 + (std::rand() % 10)) * ((std::rand() % 1) ? -1 : 1);

        world_.add<anim_component>(e).play_ = ned_anim_->play(scenimp::nanim::loop);
        world_.add<life_component>(e).life_ = remaining_ticks_ > 0 ? std::rand() % remaining_ticks_ : 1;

        world_.changed(e);
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
