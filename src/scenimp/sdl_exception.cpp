#include "sdl_exception.h"

namespace scenimp {

sdl_exception::sdl_exception()
    : runtime_error(SDL_GetError())
{
}

}
