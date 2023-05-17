#ifndef MEMORY_TRACER_H_
#define MEMORY_TRACER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <string.h>
// Traced allocations
extern void * traced_calloc(size_t size, size_t lineNumber, char const * caller, char const * fileName);
extern void traced_free(void * pointer);
extern void * traced_malloc(size_t size, size_t lineNumber, char const * caller, char const * fileName);
extern void * traced_realloc(void * pointer, size_t size, size_t lineNumber, char const * caller,
                             char const * fileName);

// Initializing the memory tracer
extern void memory_tracer_init(void);

#define __PRETTY_FILE__        (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Redefining malloc, calloc realloc and free
#define malloc(size)           traced_malloc(size, __LINE__, __func__, __PRETTY_FILE__)
#define calloc(size)           traced_calloc(size, __LINE__, __func__, __PRETTY_FILE__)
#define realloc(pointer, size) traced_realloc(pointer, size, __LINE__, __func__, __PRETTY_FILE__)
#define free(pointer)          traced_free(pointer)

int MemoryMan_Main(int argc, char const ** argv);

// Redefine main fuction
#define main(...)                          \
    main(int argc, char const ** argv) {   \
        memory_tracer_init();              \
        return MemoryMan_Main(argc, argv); \
    }                                      \
    int MemoryMan_Main(int argc, char const ** argv)

#ifdef __cplusplus
}
#endif

#endif
