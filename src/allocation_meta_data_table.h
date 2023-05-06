#ifndef ALLOCATION_META_DATA_TABLE_H_
#define ALLOCATION_META_DATA_TABLE_H_

#include <stddef.h>

#include "allocation_meta_data.h"

typedef struct {
    /// @brief The key of an entry - the pointer
    void * key;
    /// @brief The metadata of the allocation
    allocation_meta_data_t * data;
} allocation_meta_data_table_entry_t;

typedef struct {
    size_t allocated;
    size_t used;
    allocation_meta_data_table_entry_t ** entries;
} allocation_meta_data_table_t;

allocation_meta_data_table_t * allocation_meta_data_table_new();
void allocation_meta_data_table_destory(allocation_meta_data_table_t ** table);

int allocation_meta_data_table_init(allocation_meta_data_table_t * table);
void allocation_meta_data_table_free_entries(allocation_meta_data_table_t * table);
int allocation_meta_data_table_insert_entry(allocation_meta_data_table_entry_t * entry,
                                            allocation_meta_data_table_t * table);
allocation_meta_data_table_entry_t * allocation_meta_data_table_remove_entry(void * key,
                                                                             allocation_meta_data_table_t * table);
allocation_meta_data_table_entry_t * allocation_meta_data_table_look_up_entry(void * key,
                                                                              allocation_meta_data_table_t * table);

void allocation_meta_data_table_entry_destroy(allocation_meta_data_table_entry_t ** entry);
allocation_meta_data_table_entry_t * allocation_meta_data_table_entry_new(void * key, allocation_meta_data_t * data);

#endif