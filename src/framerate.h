#pragma once

#include <SDL.h>

namespace superpaflaballe {

    class framerate {
    public:
        framerate();

        bool limit();

    private:
        const int FPS_MAX = 60;
        float max_frame_ticks;
        Uint32 last_second_ticks;
        int frame_count;
        Uint32 min_ticks;
        Uint32 max_ticks;
        double average_ticks;
        Uint32 last_frame_ticks;
        Uint32 current_ticks;
        Uint32 target_ticks;
    };

}

