set(MEMORY_MAN_SOURCES
allocation_meta_data.c
allocation_meta_data_table.c
fnv1a.c
memory_tracer_internal.c
traced_allocations.c
untraced_allocations.c
)

set (MEMORY_MAN_HEADERS
allocation_meta_data.h
allocation_meta_data_table.h
fnv1a.h
memory_tracer.h
memory_tracer_internal.h
untraced_allocations.h
)
if(BUILD_SHARED_LIBS)
add_library(${PROJECT_NAME} SHARED ${MEMORY_MAN_SOURCES} ${MEMORY_MAN_HEADERS})
else()
add_library(${PROJECT_NAME} STATIC ${MEMORY_MAN_SOURCES} ${MEMORY_MAN_HEADERS})
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC -ldl)