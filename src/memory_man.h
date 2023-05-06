#ifndef MEMORY_MAN_H_
#define MEMORY_MAN_H_

#if defined(MEM_DEBUG)
#include <stddef.h>
#include <string.h>
#define __PRETTY_FILE__        (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define malloc(size)           traced_malloc(size, __func__, __LINE__, __PRETTY_FILE__)
#define calloc(size)           traced_calloc(size, __func__, __LINE__, __PRETTY_FILE__)
#define realloc(pointer, size) traced_realloc(pointer, size, __func__, __LINE__, __PRETTY_FILE__)
#define free(pointer)          traced_free(pointer)
extern void * traced_calloc(size_t size, size_t nmeb);
extern void traced_free(void * pointer);
extern void * traced_malloc(size_t size, char const * caller, size_t lineNumber, char const * fileName);
extern void * traced_realloc(void * pointer, size_t size);
extern void analyzer_init(void);

int MemoryMan_Main(int argc, char const ** argv);

// Redefine main fuction
#define main(...)                          \
    main(int argc, char const ** argv) {   \
        analyzer_init();                   \
        return MemoryMan_Main(argc, argv); \
    }                                      \
    int MemoryMan_Main(int argc, char const ** argv)
#endif

#endif /* MEMORY_MAN_H_ */
