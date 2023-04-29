#ifndef MEMORY_MAN_H_
#define MEMORY_MAN_H_

#if defined(MEM_DEBUG)
#include <stddef.h>
#include <string.h>
#define __PRETTY_FILE__        (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define malloc(size)           mm_malloc(size, __func__, __LINE__, __PRETTY_FILE__)
#define calloc(size)           mm_calloc(size, __func__, __LINE__, __PRETTY_FILE__)
#define realloc(pointer, size) mm_realloc(pointer, size, __func__, __LINE__, __PRETTY_FILE__)
#define free(pointer)          mm_free(pointer)
extern void * mm_calloc(size_t size, size_t nmeb);
extern void mm_free(void * pointer);
extern void * mm_malloc(size_t size, char const * caller, size_t lineNumber, char const * fileName);
extern void * mm_realloc(void * pointer, size_t size);
extern void analyzer_init(void);

int MemoryMan_Main(int argc, char ** argv);

// Redefine main fuction
#define main(...)                          \
    main(int argc, char ** argv) {         \
        analyzer_init();                   \
        return MemoryMan_Main(argc, argv); \
    }                                      \
    int MemoryMan_Main(int argc, char ** argv)
#endif

#endif /* MEMORY_MAN_H_ */
