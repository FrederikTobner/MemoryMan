#ifndef POINTER_TABLE_H_
#define POINTER_TABLE_H_

#if defined(MEM_DEBUG)

#include "table.h"

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
    allocation_meta_data_t data;
} pointer_table_entry_t;

GENERATE_TABLE_ENTRY_TYPE(pointer_t)

GENERATE_TABLE_TYPE(pointer_t)

GENERATE_TABLE_PROTOTYPES(pointer_t)

#endif

#endif /* POINTER_TABLE_H_ */