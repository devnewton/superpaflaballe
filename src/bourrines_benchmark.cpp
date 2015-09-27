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

        move_system(scenimp::screen& s)
        : screen_(s) {
        }

        virtual bool accept(bourrines::entity e) override {
            return has<sprite_component>(e) && has<dir_component>(e);
        }

        virtual void process(bourrines::entity e) override {
            auto& sprite = get<sprite_component>(e).sprite_;

            sprite->set_angle(sprite->angle() + 1.0);

            auto& pos = sprite->pos();
            dir_component& dir = get<dir_component>(e);
            pos.x(pos.x() + dir.dx_);
            pos.y(pos.y() + dir.dy_);
            if (pos.x() < 0) {
                dir.dx_ = -dir.dx_;
            }
            if (pos.y() < 0) {
                dir.dy_ = -dir.dy_;
            }
            if (pos.x() >= screen_.logical_screen_width()) {
                dir.dx_ = -dir.dx_;
            }
            if (pos.y() >= screen_.logical_screen_height()) {
                dir.dy_ = -dir.dy_;
            }
        }

    private:
        scenimp::screen& screen_;

    };

    class render_system : public bourrines::basic_system<world> {
    public:

        render_system(scenimp::scene& s)
        : scene_(s) {
        }

        virtual void process() override {
            scene_.render();
        }
        
    private:
        scenimp::scene& scene_;
    };

    bourrines_benchmark::bourrines_benchmark(scenimp::screen& screen, int num_entity, int num_ticks)
    : screen_(screen)
    , scene_(screen.renderer())
    , remaining_ticks_(num_ticks) {
        timer_.stop();
        ned_anim_ = screen.assets().animations("ned.json");
        world_.add_system(1, std::unique_ptr<hera_system>(new hera_system(*this, num_entity)));
        world_.add_system(2, std::unique_ptr<hades_system>(new hades_system()));
        world_.add_system(3, std::unique_ptr<move_system>(new move_system(screen)));
        world_.add_system(4, std::unique_ptr<render_system>(new render_system(scene_)));
    }

    bourrines_benchmark::~bourrines_benchmark() {
    }

    void bourrines_benchmark::create_ned() {
        bourrines::entity e = world_.create_entity();
        auto sprite = scene_.new_sprite();
        world_.add<sprite_component>(e).sprite_ = sprite;
        auto& pos = sprite->pos();

        pos.x(std::rand() % screen_.logical_screen_width());
        pos.y(std::rand() % screen_.logical_screen_height());

        dir_component& dir = world_.add<dir_component>(e);
        dir.dx_ = (1 + (std::rand() % 10)) * ((std::rand() % 1) ? -1 : 1);
        dir.dy_ = (1 + (std::rand() % 10)) * ((std::rand() % 1) ? -1 : 1);

        sprite->set_play(ned_anim_->play(scenimp::nanim::loop));
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
