cmake_minimum_required(VERSION 3.16)
project(aoc C CXX)

set(CMAKE_CXX_STANDARD 20)

set(COMPILE_OPTS -Wimplicit-fallthrough -Wall -Wundef -Wextra -Wpedantic -fdiagnostics-color=always)
add_compile_options(${COMPILE_OPTS})

add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(tests)