#include <stdio.h>
#include <stdlib.h>

#include "allocation_meta_data.h"
#include "allocation_meta_data_table.h"
#include "memory_tracer.h"
#include "untraced_allocations.h"

static allocation_meta_data_table_t * allocationMetaDataTable = NULL;

void memory_tracer_init(void) {
    allocationMetaDataTable = untraced_malloc(sizeof(allocation_meta_data_table_t));
    allocation_meta_data_table_init(allocationMetaDataTable);
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
    allocation_meta_data_table_destory(&allocationMetaDataTable);
}

void memory_tracer_handle_allocation(void * pointer, size_t lineNumber, char const * functionName,
                                     char const * fileName) {
    allocation_meta_data_t * metaData = allocation_meta_data_new(lineNumber, functionName, fileName);
    if (!metaData) {
        exit(-1);
    }
    allocation_meta_data_table_entry_t * entry = allocation_meta_data_table_entry_new(pointer, metaData);
    allocation_meta_data_table_insert_entry(entry, allocationMetaDataTable);
}

void memory_tracer_handle_free(void * pointer) {

    allocation_meta_data_table_entry_t * entry =
        allocation_meta_data_table_remove_entry(pointer, allocationMetaDataTable);
    allocation_meta_data_table_entry_destroy(&entry);
}