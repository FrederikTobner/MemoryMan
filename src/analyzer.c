#if defined(MEM_DEBUG)

#include <stdio.h>
#include <stdlib.h>

#include "pointer_table.h"
#include "untraced_memory.h"

static pointer_table_t * pointerTable = NULL;

void analyzer_at_exit();

void analyzer_init(void) {
    pointerTable = untraced_malloc(sizeof(pointer_table_t));
    pointer_table_init_table(pointerTable);
    atexit(analyzer_at_exit);
}

void analyzer_at_exit() {
    for (size_t i = 0; i < pointerTable->allocated; i++) {
        if (pointerTable->entries[i] && pointerTable->entries[i] != (pointer_table_entry_t *)(0xFFFFFFFFFFFFFFFFUL)) {
            printf("Found memory leak %p created in function %s at line %zu in file %s\n",
                   pointerTable->entries[i]->key, pointerTable->entries[i]->data->functionName,
                   pointerTable->entries[i]->data->lineNumber, pointerTable->entries[i]->data->fileName);
        }
    }
    pointer_table_destory(&pointerTable);
}

void analyzer_add_pointer(void * pointer, char const * functionName, size_t lineNumber, char const * fileName) {
    allocation_meta_data_t * metaData = untraced_malloc(sizeof(allocation_meta_data_t));
    if (!metaData) {
        exit(-1);
    }
    metaData->functionName = functionName;
    metaData->lineNumber = lineNumber;
    metaData->fileName = fileName;
    pointer_table_entry_t * entry = pointer_table_entry_new(pointer, metaData);
    pointer_table_insert_entry(entry, pointerTable);
}

void analyzer_remove_pointer(void * pointer) {
    pointer_table_remove_entry(pointer_table_look_up_entry(pointer, pointerTable), pointerTable);
}

#endif