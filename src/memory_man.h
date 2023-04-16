#ifndef MEMORY_MAN_H_
#define MEMORY_MAN_H_

#ifdef MEM_DEBUG
#include <stddef.h>
extern void * calloc(size_t size);
extern void free(void * pointer);
extern void * malloc(size_t size);
#endif

#endif /* MEMORY_MAN_H_ */
