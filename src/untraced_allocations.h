#ifndef UNTRACED_MEMORY_MAN_H_
#define UNTRACED_MEMORY_MAN_H_

#include <stddef.h>

void * untraced_malloc(size_t size);

void * untraced_realloc(void * pointer, size_t size);

void * untraced_calloc(size_t size);

void untraced_free(void * pointer);

#endif