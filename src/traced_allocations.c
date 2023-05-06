#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdint.h>

#include "allocation_meta_data_table.h"
#include "memory_tracer.h"
#include "untraced_allocations.h"

void traced_free(void * pointer) {
    untraced_free(pointer);
    memory_tracer_handle_free(pointer);
}

void * traced_calloc(size_t size, size_t lineNumber, char const * caller, char const * fileName) {
    void * p = untraced_calloc(size);
    memory_tracer_handle_allocation(p, lineNumber, caller, fileName);
    return p;
}

void * traced_malloc(size_t size, size_t lineNumber, char const * caller, char const * fileName) {
    void * p = untraced_malloc(size);
    memory_tracer_handle_allocation(p, lineNumber, caller, fileName);
    return p;
}

void * traced_realloc(void * pointer, size_t size, size_t lineNumber, char const * caller, char const * fileName) {
    void * p = untraced_realloc(pointer, size);
    memory_tracer_handle_free(pointer);
    memory_tracer_handle_allocation(p, lineNumber, caller, fileName);
    return p;
}