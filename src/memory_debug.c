#if defined(MEM_DEBUG)
#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>

#include "pointer_table.h"

void free(void * pointer) {
    static void (*real_free)(void *) = NULL;
    if (!real_free) {
        real_free = dlsym(RTLD_NEXT, "free");
    }
    fprintf(stdout, "freed %p", pointer);
    real_free(pointer);
}

void * calloc(size_t size, size_t nmeb) {
    static void * (*real_calloc)(size_t) = NULL;
    if (!real_calloc) {
        real_calloc = dlsym(RTLD_NEXT, "calloc");
    }
    void * p = real_calloc(size);
    fprintf(stdout, "calloc(%zu) = %p\n", size, p);
    return p;
}

void * malloc(size_t size) {
    static void * (*real_malloc)(size_t) = NULL;
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    void * p = real_malloc(size);
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
    fprintf(stdout, "realloc(%p, %zu) = %p\n", pointer, size, p);
    return p;
}

#endif