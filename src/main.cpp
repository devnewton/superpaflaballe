#include "scenimp/assets.h"
#include "scenimp/screen.h"
#include "intro.h"
#include "bourrines_benchmark.h"
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <SDL2_framerate.h>

namespace superpaflaballe {
    namespace statechart {

        struct event_sdl : boost::statechart::event< event_sdl > {
            SDL_Event e_;
        };

        struct event_tick : boost::statechart::event< event_tick > {
        };

        struct state_running;
        struct state_intro;
        struct state_benchmark;
        struct state_outro;

        struct machine : boost::statechart::state_machine< machine, state_running > {
            scenimp::screen screen_;
        };

        struct state_running : boost::statechart::simple_state< state_running, machine, state_intro > {
            typedef boost::statechart::custom_reaction< event_sdl > reactions;

            boost::statechart::result react(const event_sdl& event) {
                if (event.e_.type == SDL_QUIT) {
                    return terminate();
                } else {
                    return forward_event();
                }
            }
        };

        struct state_intro : boost::statechart::state< state_intro, state_running > {
            typedef boost::mpl::list<
            boost::statechart::custom_reaction< event_tick >,
            boost::statechart::custom_reaction< event_sdl >
            > reactions;

            state_intro(my_context ctx)
            : boost::statechart::state< state_intro, state_running >(ctx)
            , intro_(this->outermost_context().screen_) {
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
                    return forward_event();
                }
            }
            intro intro_;
        };

        struct state_benchmark : boost::statechart::state< state_benchmark, state_running > {
            typedef boost::statechart::custom_reaction< event_tick > reactions;

            state_benchmark(my_context ctx)
            : boost::statechart::state< state_benchmark, state_running >(ctx)
            , benchmark_(this->outermost_context().screen_, 1000, 60 * 10) {
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

        struct state_outro : boost::statechart::state< state_outro, state_running > {

            state_outro(my_context ctx)
            : boost::statechart::state< state_outro, state_running >(ctx) {
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
        
        FPSmanager fps;
        SDL_initFramerate(&fps);
        SDL_setFramerate(&fps, 60);
        while (!machine.terminated()) {
            while (SDL_PollEvent(&event_sdl.e_)) {
                machine.process_event(event_sdl);
            }
            SDL_RenderClear(machine.screen_.renderer());
            machine.process_event(event_tick);
            SDL_RenderPresent(machine.screen_.renderer());
            SDL_framerateDelay(&fps);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error " << e.what() << std::endl;
    }
}
