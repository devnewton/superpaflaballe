#include "sdl_exception.h"

namespace superpaflaballe {

sdl_exception::sdl_exception()
    : runtime_error(SDL_GetError())
{
}

}
