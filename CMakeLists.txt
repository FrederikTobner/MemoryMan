cmake_minimum_required(VERSION 3.16)
project(MemoryMan VERSION 1.0.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

if(CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
    add_compile_definitions(MEM_DEBUG)
endif()

add_subdirectory(src)

add_subdirectory(example)