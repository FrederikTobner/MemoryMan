#ifndef POINTER_TABLE_H_
#define POINTER_TABLE_H_

#if defined(MEM_DEBUG)

#include <stddef.h>

typedef void * pointer_t;

typedef struct {
    size_t lineNumber;
    char const * functionName;
    char const * fileName;
} allocation_meta_data_t;

// TODO: Create a table with based on the following entry without any macros, because that will be easier
typedef struct {
    void * key;
    allocation_meta_data_t * data;
} pointer_table_entry_t;

typedef struct {
    size_t allocated;
    size_t used;
    pointer_table_entry_t ** entries;
} pointer_table_t;

pointer_table_entry_t * pointer_table_entry_new(void * key, allocation_meta_data_t * data);
int pointer_table_init_table(pointer_table_t * table);
pointer_table_t * pointer_table_new();
void pointer_table_destory(pointer_table_t ** table);
void pointer_table_free_entries(pointer_table_t * table);
int pointer_table_insert_entry(pointer_table_entry_t * entry, pointer_table_t * table);
pointer_table_entry_t * pointer_table_remove_entry(pointer_table_entry_t * entry, pointer_table_t * table);
pointer_table_entry_t * pointer_table_look_up_entry(void * key, pointer_table_t * table);

#endif

#endif /* POINTER_TABLE_H_ */