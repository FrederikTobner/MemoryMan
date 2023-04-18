#if defined(MEM_DEBUG)
#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>

#include "analyzer.h"
#include "pointer_table.h"

void free(void * pointer) {
    static void (*real_free)(void *) = NULL;
    if (!real_free) {
        real_free = dlsym(RTLD_NEXT, "free");
    }
    real_free(pointer);
}

void * calloc(size_t size, size_t nmeb) {
    static void * (*real_calloc)(size_t) = NULL;
    if (!real_calloc) {
        real_calloc = dlsym(RTLD_NEXT, "calloc");
    }
    void * p = real_calloc(size);
    return p;
}

void * mm_malloc(size_t size, char const * caller, size_t lineNumber, char const * fileName) {
    static void * (*real_malloc)(size_t) = NULL;
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    void * p = real_malloc(size);
    analyzer_add_pointer(caller, p);
    return p;
}

void * untraced_malloc(size_t size) {
    static void * (*real_malloc)(size_t) = NULL;
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    void * p = real_malloc(size);
    return p;
}

void * realloc(void * pointer, size_t size) {
    static void * (*real_realloc)(void *, size_t) = NULL;
    if (!real_realloc) {
        real_realloc = dlsym(RTLD_NEXT, "realloc");
    }
    void * p = real_realloc(pointer, size);
    return p;
}

#endif