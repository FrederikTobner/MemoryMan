#if defined(MEM_TRACE) && !defined(NDEBUG)

#include <stdio.h>
#include <stdlib.h>

#include "allocation_meta_data_table.h"
#include "memory_tracer.h"
#include "untraced_allocations.h"

static allocation_meta_data_table_t * allocationMetaDataTable = NULL;

void memory_tracer_init(void) {
    allocationMetaDataTable = untraced_malloc(sizeof(allocation_meta_data_table_t));
    pointer_table_init_table(allocationMetaDataTable);
    atexit(memory_tracer_at_exit);
}

void memory_tracer_at_exit() {
    for (size_t i = 0; i < allocationMetaDataTable->allocated; i++) {
        if (allocationMetaDataTable->entries[i] &&
            allocationMetaDataTable->entries[i] != (allocation_meta_data_table_entry_t *)(0xFFFFFFFFFFFFFFFFUL)) {
            printf("Found memory leak %p created in function %s at line %zu in file %s\n",
                   allocationMetaDataTable->entries[i]->key, allocationMetaDataTable->entries[i]->data->functionName,
                   allocationMetaDataTable->entries[i]->data->lineNumber,
                   allocationMetaDataTable->entries[i]->data->fileName);
        }
    }
    pointer_table_destory(&allocationMetaDataTable);
}

void memory_tracer_handle_allocation(void * pointer, char const * functionName, size_t lineNumber,
                                     char const * fileName) {
    allocation_meta_data_t * metaData = untraced_malloc(sizeof(allocation_meta_data_t));
    if (!metaData) {
        exit(-1);
    }
    metaData->functionName = functionName;
    metaData->lineNumber = lineNumber;
    metaData->fileName = fileName;
    allocation_meta_data_table_entry_t * entry = pointer_table_entry_new(pointer, metaData);
    pointer_table_insert_entry(entry, allocationMetaDataTable);
}

void memory_tracer_handle_free(void * pointer) {

    allocation_meta_data_table_entry_t * entry = pointer_table_remove_entry(pointer, allocationMetaDataTable);
    untraced_free(entry->data);
    untraced_free(entry);
}

#endif