#include "allocation_meta_data_table.h"

#include <stdint.h>
#include <stdlib.h>

#include "fnv1a.h"
#include "untraced_allocations.h"

#define TABLE_TOMBSTONE                (allocation_meta_data_table_entry_t *)(0xFFFFFFFFFFFFFFFFUL)

#define POINTER_SIZE                   sizeof(void *)

/// Size check using a type (used for the checked malloc)
#define SIZE_CHECK_USING_TYPE(n, type) ((SIZE_MAX / sizeof(type)) >= (n))

/// @brief Checked malloc using the type
/// @details Treats a overflow parameters when malloc was called like a usual
/// allocation error
#define CHECKED_MALLOC_USING_TYPE(n, type) \
    (SIZE_CHECK_USING_TYPE((n), (type)) ? untraced_malloc((n) * sizeof(type)) : 0)

/// The growth factor of a hashtable - we double the size of the table every time a growth is triggered
#define GROWTH_FACTOR              (2)

/// The growth trigger value of a hashtables
#define TABLE_GROWTH_TRIGGER_VALUE (0.75)

/// The initial size of a hashtables
#define TABLE_INIT_SIZE            (8)

static int allocation_meta_data_table_grow_table(allocation_meta_data_table_t *);

allocation_meta_data_table_t * allocation_meta_data_table_new() {
    allocation_meta_data_table_t * table = untraced_malloc(sizeof(allocation_meta_data_table_t));
    if (!table) {
        return NULL;
    }
    allocation_meta_data_table_init(table);
    return table;
}

allocation_meta_data_table_entry_t * allocation_meta_data_table_entry_new(void * key, allocation_meta_data_t * data) {
    if (!key || !data) {
        return NULL;
    }
    allocation_meta_data_table_entry_t * entry = untraced_malloc(sizeof(allocation_meta_data_table_entry_t));
    if (!entry) {
        return NULL;
    }
    entry->data = data;
    entry->key = key;
    return entry;
}

void allocation_meta_data_table_entry_destroy(allocation_meta_data_table_entry_t ** entry) {
    if (entry && *entry) {
        untraced_free((*entry)->data);
        untraced_free(*entry);
        *entry = NULL;
    }
}

void allocation_meta_data_table_destory(allocation_meta_data_table_t ** table) {
    if (!table || !*table) {
        return;
    }
    allocation_meta_data_table_free_entries(*table);
    untraced_free(*table);
    *table = NULL;
}

int allocation_meta_data_table_init(allocation_meta_data_table_t * table) {
    if (!table) {
        return -1;
    }
    table->used = 0;
    table->allocated = TABLE_INIT_SIZE;
    table->entries = untraced_malloc(table->allocated * sizeof(allocation_meta_data_table_entry_t));
    if (!table->entries) {
        return -1;
    }
    for (size_t i = 0; i < table->allocated; i++) {
        table->entries[i] = NULL;
    }
    return 0;
}

void allocation_meta_data_table_free_entries(allocation_meta_data_table_t * table) {
    if (!table || !table->entries) {
        return;
    }
    for (size_t i = 0; i < table->allocated; i++) {
        if (!table->entries[i] || table->entries[i] == TABLE_TOMBSTONE) {
            break;
        }
        if (table->entries[i]->data) {
            untraced_free(table->entries[i]->data);
        }
    }
    untraced_free(table->entries);
    table->allocated = table->used = 0;
    table->entries = NULL;
}

int allocation_meta_data_table_insert_entry(allocation_meta_data_table_entry_t * node,
                                            allocation_meta_data_table_t * table) {
    if (!node || !table) {
        return -1;
    }
    if (table->used >= ((double)table->allocated) * TABLE_GROWTH_TRIGGER_VALUE) {
        if (allocation_meta_data_table_grow_table(table)) {
            return -1;
        }
    }
    uint32_t index, try;
    index = fnv1a_hash_data((uint64_t)node->key, POINTER_SIZE);
    for (size_t i = 0; i < table->allocated; i++) {
        try = (i + index) & (table->allocated - 1);
        if (!table->entries[try] || table->entries[try] == TABLE_TOMBSTONE) {
            table->entries[try] = node;
            table->used++;
            return 0;
        }
    }
    return -1;
}

allocation_meta_data_table_entry_t * allocation_meta_data_table_remove_entry(void * key,
                                                                             allocation_meta_data_table_t * table) {
    if (!table || !key) {
        return NULL;
    }
    uint32_t index, try;
    index = fnv1a_hash_data((uint64_t)key, POINTER_SIZE);
    for (uint32_t i = 0; i < table->allocated; i++) {
        try = (i + index) & (table->allocated - 1);
        if (!table->entries[try]) {
            return 0;
        }
        if (table->entries[try] != TABLE_TOMBSTONE && table->entries[try]->key == key) {
            allocation_meta_data_table_entry_t * tempNode = table->entries[try];
            table->entries[try] = TABLE_TOMBSTONE;
            table->used--;
            return tempNode;
        }
    }
    return NULL;
}

allocation_meta_data_table_entry_t * allocation_meta_data_table_look_up_entry(void * key,
                                                                              allocation_meta_data_table_t * table) {
    if (!table) {
        return NULL;
    }
    uint32_t index = fnv1a_hash_data((uint64_t)key, POINTER_SIZE);
    for (uint32_t i = 0; i < table->allocated; i++) {
        uint32_t try = (i + index) & (table->allocated - 1);
        if (!table->entries[try]) {
            return NULL;
        }
        if (table->entries[try]->key == key) {
            return table->entries[try];
        }
    }
    return NULL;
}

static int allocation_meta_data_table_grow_table(allocation_meta_data_table_t * table) {
    allocation_meta_data_table_entry_t ** newEntries =
        CHECKED_MALLOC_USING_TYPE(table->allocated * GROWTH_FACTOR, *table->entries);
    if (!newEntries) {
        return -1;
    }
    for (size_t i = 0; i < table->allocated * GROWTH_FACTOR; i++) {
        newEntries[i] = NULL;
    }
    allocation_meta_data_table_entry_t ** oldEntries = table->entries;
    table->entries = newEntries;
    table->used = 0;
    for (size_t j = 0; j < table->allocated; j++) {
        allocation_meta_data_table_insert_entry(oldEntries[j], table);
    }
    table->allocated *= GROWTH_FACTOR;
    untraced_free(oldEntries);
    return 0;
}