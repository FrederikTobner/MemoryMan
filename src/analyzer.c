#if defined(MEM_DEBUG)

#include <stdio.h>

#include "pointer_table.h"
#include "untraced_memory.h"

static pointer_t_table_t * pointerTable = NULL;

void analyzer_at_exit();

void analyzer_init(void) {
    pointerTable = untraced_malloc(sizeof(pointer_t_table_t));
    pointer_t_table_init_table(pointerTable);
    atexit(analyzer_at_exit);
}

void analyzer_at_exit() {
    for (size_t i = 0; i < pointerTable->allocated; i++) {
        if (pointerTable->entries[i]) {
            printf("Found memory leak %p created in function %s\n", pointerTable->entries[i]->data,
                   pointerTable->entries[i]->key);
        }
    }
    pointer_t_table_destory(&pointerTable);
}

void analyzer_add_pointer(char const * name, void * pointer) {
    pointer_t_table_entry_t * entry = pointer_t_table_entry_new(pointer, name);
    pointer_t_table_insert_entry(entry, pointerTable);
}

#endif