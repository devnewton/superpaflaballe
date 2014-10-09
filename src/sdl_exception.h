#pragma once

#include <SDL.h>
#include <stdexcept>

namespace superpaflaballe {

class sdl_exception : public std::runtime_error
{
public:
    sdl_exception();
};

}
