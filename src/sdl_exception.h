#ifndef superpaflaballe_sdl_exception_h
#define superpaflaballe_sdl_exception_h

#include <SDL.h>
#include <stdexcept>

namespace superpaflaballe {

class sdl_exception : public std::runtime_error
{
public:
    sdl_exception();
};

}

#endif
