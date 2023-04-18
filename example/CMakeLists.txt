add_executable(MemoryManExample main.c)

target_link_libraries(MemoryManExample MemoryMan)

target_include_directories(MemoryManExample PUBLIC ../src)