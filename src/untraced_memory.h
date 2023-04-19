#ifndef UNTRACED_MEMORY_MAN_H_
#define UNTRACED_MEMORY_MAN_H_

#include <stddef.h>

extern void * untraced_malloc(size_t size);

extern void untraced_free(void * pointer);

#endif