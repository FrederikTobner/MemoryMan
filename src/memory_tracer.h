#ifndef MEMORY_ANALYZER_H_
#define MEMORY_ANALYZER_H_

#include <stddef.h>

void memory_tracer_handle_allocation(void * pointer, char const * functionName, size_t lineNumber,
                                     char const * fileName);

void memory_tracer_handle_free(void * pointer);

void memory_tracer_at_exit();

#endif