set(MEMORY_MAN_SOURCES
analyzer.c
memory_debug.c
pointer_table.c
)

set (MEMORY_MAN_HEADERS
analyzer.h
memory_man.h
pointer_table.h
table.h
untraced_memory.h
)

add_library(${PROJECT_NAME} STATIC ${MEMORY_MAN_SOURCES} ${MEMORY_MAN_HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC -ldl)
