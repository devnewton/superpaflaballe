#include "framerate.h"

namespace superpaflaballe {

    framerate::framerate() {
        max_frame_ticks = (1000.0 / (float) FPS_MAX) + 0.00001;
        frame_count = 0;
        last_second_ticks = SDL_GetTicks();
    }

    bool framerate::limit() {
        frame_count++;
        target_ticks = last_second_ticks + Uint32(frame_count * max_frame_ticks);
        current_ticks = SDL_GetTicks();
        average_ticks += current_ticks - last_frame_ticks;
        if (current_ticks - last_frame_ticks <= min_ticks) {
            min_ticks = current_ticks - last_frame_ticks;
        }
        if (current_ticks - last_frame_ticks >= max_frame_ticks) {
            max_ticks = current_ticks - last_frame_ticks;
        }
        if (current_ticks < target_ticks) {
            SDL_Delay(target_ticks - current_ticks);
            current_ticks = SDL_GetTicks();
        }
        last_frame_ticks = current_ticks;
        if (current_ticks - last_second_ticks >= 1000) {
            frame_count = 0;
            min_ticks = 1000;
            max_ticks = 0;
            average_ticks = 0;
            last_second_ticks = SDL_GetTicks();
            return true;
        }
        return false;
    }

}
