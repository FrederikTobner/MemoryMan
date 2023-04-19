#ifndef MEMORY_ANALYZER_H_
#define MEMORY_ANALYZER_H_

#include <stddef.h>

void analyzer_add_pointer(void * pointer, char const * functionName, size_t lineNumber, char const * fileName);

void analyzer_remove_pointer(void * pointer);

#endif