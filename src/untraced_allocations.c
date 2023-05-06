#if defined(MEM_TRACE) && !defined(NDEBUG)
#define _GNU_SOURCE
#include <dlfcn.h>

#include "untraced_allocations.h"

void * untraced_malloc(size_t size) {
    static void * (*real_malloc)(size_t) = NULL;
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    void * p = real_malloc(size);
    return p;
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
#endif