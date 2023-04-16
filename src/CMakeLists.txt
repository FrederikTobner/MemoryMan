set(MEMORY_MAN_SOURCES
memory_debug.c
)

set (MEMORY_MAN_HEADERS
memory_man.h
)


add_library(${PROJECT_NAME} ${MEMORY_MAN_SOURCES} ${MEMORY_MAN_HEADERS})