#define _GNU_SOURCE
#include <dlfcn.h>

#include "untraced_allocations.h"

void * untraced_malloc(size_t size) {
    static void * (*real_malloc)(size_t) = NULL;
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    return real_malloc(size);
}

void * untraced_calloc(size_t size) {
    static void * (*real_calloc)(size_t) = NULL;
    if (!real_calloc) {
        real_calloc = dlsym(RTLD_NEXT, "calloc");
    }
    return real_calloc(size);
}

void * untraced_realloc(void * pointer, size_t size) {
    static void * (*real_realloc)(void *, size_t) = NULL;
    if (!real_realloc) {
        real_realloc = dlsym(RTLD_NEXT, "realloc");
    }
    return real_realloc(pointer, size);
}

void untraced_free(void * pointer) {
    if (!pointer) {
        return;
    }
    static void (*real_free)(void *) = NULL;
    if (!real_free) {
        real_free = dlsym(RTLD_NEXT, "free");
    }
    real_free(pointer);
}