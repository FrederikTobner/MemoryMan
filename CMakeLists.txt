cmake_minimum_required(VERSION 3.16)
project(MemoryMan VERSION 1.0.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

option(BUILD_EXAMPLE "Build example" ON)
option(BUILD_SHARED_LIBS "shared/static libs" ON) # OFF for static libs

add_subdirectory(src)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()