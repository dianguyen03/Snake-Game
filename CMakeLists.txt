cmake_minimum_required(VERSION 3.21)
project(snake C)

set(CMAKE_C_STANDARD 11)

# add the path to the SDL2 framework
set(SDL2_PATH "/Library/Frameworks/SDL2.framework")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})



add_executable(snake main.c
        game.c
        game.h
)

target_link_libraries(snake PRIVATE SDL2::SDL2)