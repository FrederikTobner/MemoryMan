set(MEMORY_MAN_SOURCES
allocation_meta_data_table.c
memory_tracer.c
traced_allocations.c
untraced_allocations.c
)

set (MEMORY_MAN_HEADERS
allocation_meta_data_table.h
memory_tracer.h
memory_man.h
untraced_allocations.h
)

add_library(${PROJECT_NAME} STATIC ${MEMORY_MAN_SOURCES} ${MEMORY_MAN_HEADERS})
target_link_libraries(${PROJECT_NAME} PUBLIC -ldl)