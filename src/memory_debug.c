#ifdef MEM_DEBUG
#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>

void free(void * pointer) {
    static void (*real_free)(void *) = NULL;
    if (!real_free) {
        real_free = dlsym(RTLD_NEXT, "free");
    }
    fprintf(stdout, "freed %p", pointer);
    real_free(pointer);
}

void * calloc(size_t size) {
    static void * (*real_calloc)(size_t) = NULL;
    if (!real_malloc) {
        real_malloc = dlsym(RTLD_NEXT, "calloc");
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
    fprintf(stdout, "malloc(%zu) = %p\n", size, p);
    return p;
}

#endif