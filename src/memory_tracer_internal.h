#ifndef MEMORY_TRACER_H_
#define MEMORY_TRACER_H_

#include <stddef.h>

void memory_tracer_handle_allocation(void * pointer, size_t lineNumber, char const * functionName,
                                     char const * fileName);

void memory_tracer_handle_free(void * pointer);

void memory_tracer_at_exit();

#endif