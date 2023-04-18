#ifndef MEMORY_MAN_H_
#define MEMORY_MAN_H_

#if defined(MEM_DEBUG)
#include <stddef.h>
extern void * calloc(size_t size, size_t nmeb);
extern void free(void * pointer);
extern void * malloc(size_t size);
extern void * realloc(void * pointer, size_t size);
extern void memory_man_init(void);

int MemoryMan_Main(int argc, char ** argv);

// Redefine main fuction
#define main(...)                          \
    main(int argc, char ** argv) {         \
        memory_man_init();                 \
        return MemoryMan_Main(argc, argv); \
    }                                      \
    int MemoryMan_Main(int argc, char ** argv)
#endif

#endif /* MEMORY_MAN_H_ */
