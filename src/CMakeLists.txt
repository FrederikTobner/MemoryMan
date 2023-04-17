set(MEMORY_MAN_SOURCES
pointer_table.c
memory_debug.c
)

set (MEMORY_MAN_HEADERS
memory_man.h
pointer_table.h
table.h
)

if(CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
    add_compile_definitions(DEBUG_BUILD)
endif()

add_library(${PROJECT_NAME} ${MEMORY_MAN_SOURCES} ${MEMORY_MAN_HEADERS})
