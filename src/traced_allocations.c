#if defined(MEM_DEBUG)
#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdint.h>

#include "allocation_data_table.h"
#include "analyzer.h"
#include "untraced_allocations.h"

void traced_free(void * pointer) {
    untraced_free(pointer);
    analyzer_remove_pointer(pointer);
}

void * traced_calloc(size_t size, char const * caller, size_t lineNumber, char const * fileName) {
    static void * (*real_calloc)(size_t) = NULL;
    if (!real_calloc) {
        real_calloc = dlsym(RTLD_NEXT, "calloc");
    }
    void * p = real_calloc(size);
    analyzer_add_pointer(p, caller, lineNumber, fileName);
    return p;
}

void * traced_malloc(size_t size, char const * caller, size_t lineNumber, char const * fileName) {
    void * p = untraced_malloc(size);
    analyzer_add_pointer(p, caller, lineNumber, fileName);
    return p;
}

void * traced_realloc(void * pointer, size_t size, char const * caller, size_t lineNumber, char const * fileName) {
    static void * (*real_realloc)(void *, size_t) = NULL;
    if (!real_realloc) {
        real_realloc = dlsym(RTLD_NEXT, "realloc");
    }
    void * p = real_realloc(pointer, size);
    analyzer_remove_pointer(pointer);
    analyzer_add_pointer(p, caller, lineNumber, fileName);
    return p;
}

#endif