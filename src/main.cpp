#include "assets.h"
#include "game.h"
#include "framerate.h"
#include "intro.h"
#include "bourrines_benchmark.h"
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace superpaflaballe {
    namespace statechart {

        struct event_sdl : boost::statechart::event< event_sdl >  {
            SDL_Event e_;
        };

        struct event_tick : boost::statechart::event< event_tick > {
        };

        struct state_intro;
        struct state_benchmark;
        struct state_outro;

        struct machine : boost::statechart::state_machine< machine, state_intro > {
            game game_;
            framerate framerate_;
        };

        struct state_intro : boost::statechart::state< state_intro, machine > {
            typedef boost::mpl::list<
            boost::statechart::custom_reaction< event_tick >,
            boost::statechart::custom_reaction< event_sdl >
            > reactions;

            state_intro(my_context ctx)
            : boost::statechart::state< state_intro, machine >(ctx)
            , intro_(this->outermost_context().game_) {
            }

            boost::statechart::result react(const event_tick&) {
                intro_.tick();
                if (intro_.is_finished()) {
                    return transit<state_benchmark>();
                } else {
                    return discard_event();
                }
            }

            boost::statechart::result react(const event_sdl& event) {
                if (event.e_.type == SDL_KEYUP) {
                    return transit<state_benchmark>();
                } else {
                    return discard_event();
                }
            }
            intro intro_;
        };

        struct state_benchmark : boost::statechart::state< state_benchmark, machine > {
            typedef boost::statechart::custom_reaction< event_tick > reactions;

            state_benchmark(my_context ctx)
            : boost::statechart::state< state_benchmark, machine >(ctx)
            , benchmark_(this->outermost_context().game_, 10000, 60 * 10) {
            }

            boost::statechart::result react(const event_tick&) {
                benchmark_.tick();
                if (benchmark_.is_finished()) {
                    return transit<state_outro>();
                } else {
                    return discard_event();
                }
            }
            bourrines_benchmark benchmark_;
        };

        struct state_outro : boost::statechart::state< state_outro, machine > {

            state_outro(my_context ctx)
            : boost::statechart::state< state_outro, machine >(ctx) {
            }
        };
    }
}

int main(int, char**) {
    try {
        superpaflaballe::statechart::machine machine;
        machine.initiate();

        superpaflaballe::statechart::event_sdl event_sdl;
        superpaflaballe::statechart::event_tick event_tick;
        for (;;) {
            while (SDL_PollEvent(&event_sdl.e_)) {
                if (event_sdl.e_.type == SDL_QUIT) {
                    return 0;
                }
                machine.process_event(event_sdl);
            }
            SDL_RenderClear(machine.game_.renderer());
            machine.process_event(event_tick);
            SDL_RenderPresent(machine.game_.renderer());
            machine.framerate_.limit();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error " << e.what() << std::endl;
    }
}
