cmake_minimum_required(VERSION 2.8)
project ( superpaflaballe )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${superpaflaballe_SOURCE_DIR}/cmake")

add_definitions(-DPREFIX="${CMAKE_INSTALL_PREFIX}") 

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
endif()

find_package(Boost REQUIRED COMPONENTS filesystem system timer)
include_directories( ${Boost_INCLUDE_DIRS} )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_executable(superpaflaballe src/assets.cpp src/bourrines_benchmark.cpp src/framerate.cpp src/game.cpp src/intro.cpp src/main.cpp src/nanim.cpp src/sdl_exception.cpp)
target_link_libraries(superpaflaballe ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${Boost_LIBRARIES})
