set(MEMORY_MAN_SOURCES
pointer_table.c
memory_debug.c
initialize.c
)

set (MEMORY_MAN_HEADERS
memory_man.h
pointer_table.h
table.h
untraced_memory.h
)

add_library(${PROJECT_NAME} STATIC ${MEMORY_MAN_SOURCES} ${MEMORY_MAN_HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC -ldl)
