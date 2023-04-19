#include "pointer_table.h"

#if defined(MEM_DEBUG)

#include <stdint.h>
#include <stdlib.h>

#include "untraced_memory.h"

#define OFFSET_BASIS                   0x811c9dc5u
#define PRIME                          0x01000193u

/// Size check using a type (used for the checked malloc)
#define SIZE_CHECK_USING_TYPE(n, type) ((SIZE_MAX / sizeof(type)) >= (n))

/// @brief Checked malloc using the type
/// @details Treats a overflow parameters when malloc was called like a usual
/// allocation error
#define CHECKED_MALLOC_USING_TYPE(n, type) \
    (SIZE_CHECK_USING_TYPE((n), (type)) ? untraced_malloc((n) * sizeof(type)) : 0)

/// The maximum length of the key of a hashtable entry
#define MAX_KEY_LENGTH             (1024)

/// The growth factor of a hashtable
#define GROWTH_FACTOR              (2)

/// The growth trigger value of a hashtables
#define TABLE_GROWTH_TRIGGER_VALUE (0.75)

/// The initial size of a hashtables
#define TABLE_INIT_SIZE            (8)

static uint32_t fnv1a_hash_data(uint8_t const * data, size_t length) {
    uint32_t hash = OFFSET_BASIS;
    for (size_t i = 0; i < length; i++) {
        hash ^= data[i];
        hash *= PRIME;
    }
    return hash;
}

static int pointer_table_grow_table(pointer_table_t *);

pointer_table_t * pointer_table_new() {
    pointer_table_t * table = untraced_malloc(sizeof(pointer_table_t));
    if (!table) {
        return NULL;
    }
    pointer_table_init_table(table);
    return table;
}

pointer_table_entry_t * pointer_table_entry_new(void * key, allocation_meta_data_t * data) {
    if (!key || !data) {
        return NULL;
    }
    pointer_table_entry_t * entry = untraced_malloc(sizeof(pointer_table_entry_t));
    if (!entry) {
        return NULL;
    }
    entry->data = data;
    entry->key = key;
    return entry;
}

void pointer_table_destory(pointer_table_t ** table) {
    if (!table || !*table) {
        return;
    }
    pointer_table_free_entries(*table);
    untraced_free(*table);
    *table = NULL;
}

int pointer_table_init_table(pointer_table_t * table) {
    if (!table) {
        return -1;
    }
    table->used = 0;
    table->allocated = TABLE_INIT_SIZE;
    table->entries = untraced_malloc(table->allocated * sizeof(pointer_table_entry_t));
    if (!table->entries) {
        return -1;
    }
    for (size_t i = 0; i < table->allocated; i++) {
        table->entries[i] = NULL;
    }
    return 0;
}

void pointer_table_free_entries(pointer_table_t * table) {
    if (!table || !table->entries) {
        return;
    }
    for (size_t i = 0; i < table->allocated; i++) {
        if (!table->entries[i] || table->entries[i] == (pointer_table_entry_t *)(0xFFFFFFFFFFFFFFFFUL)) {
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

int pointer_table_insert_entry(pointer_table_entry_t * node, pointer_table_t * table) {
    if (!node || !table) {
        return -1;
    }
    if (table->used >= ((double)table->allocated) * TABLE_GROWTH_TRIGGER_VALUE) {
        if (pointer_table_grow_table(table)) {
            return -1;
        }
    }
    uint32_t index, try;
    index = fnv1a_hash_data((uint8_t *)node->key, sizeof(void *));
    for (size_t i = 0; i < table->allocated; i++) {
        try = (i + index) & (table->allocated - 1);
        if (!table->entries[try] || table->entries[try] == (pointer_table_entry_t *)(0xFFFFFFFFFFFFFFFFUL)) {
            table->entries[try] = node;
            table->used++;
            return 0;
        }
    }
    return -1;
}

pointer_table_entry_t * pointer_table_remove_entry(pointer_table_entry_t * node, pointer_table_t * table) {
    if (!table || !node) {
        return ((void *)0);
    }
    uint32_t index = fnv1a_hash_data((uint8_t *)node->key, sizeof(void *));
    for (uint32_t i = 0; i < table->allocated; i++) {
        uint32_t try = (i + index) & (table->allocated - 1);
        if (!table->entries[try]) {
            return 0;
        }
        if (table->entries[try]->key == node->key) {
            pointer_table_entry_t * tempNode = table->entries[try];
            table->entries[try] = (pointer_table_entry_t *)(0xFFFFFFFFFFFFFFFFUL);
            table->used--;
            return tempNode;
        }
    }
    return NULL;
}

pointer_table_entry_t * pointer_table_look_up_entry(void * key, pointer_table_t * table) {
    if (!table) {
        return NULL;
    }
    uint32_t index = fnv1a_hash_data((uint8_t *)key, sizeof(void *));
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

static int pointer_table_grow_table(pointer_table_t * table) {
    pointer_table_entry_t ** newEntries = CHECKED_MALLOC_USING_TYPE(table->allocated * GROWTH_FACTOR, *table->entries);
    if (!newEntries) {
        return -1;
    }
    for (size_t i = 0; i < table->allocated * GROWTH_FACTOR; i++) {
        newEntries[i] = NULL;
    }
    pointer_table_entry_t ** oldEntries = table->entries;
    table->entries = newEntries;
    table->used = 0;
    table->allocated *= GROWTH_FACTOR;
    for (size_t j = 0; j < table->allocated / GROWTH_FACTOR; j++) {
        pointer_table_insert_entry(oldEntries[j], table);
    }
    untraced_free(oldEntries);
    return 0;
}

#endif