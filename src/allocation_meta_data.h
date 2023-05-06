#ifndef ALLOCATION_META_DATA_H_
#define ALLOCATION_META_DATA_H_

#include <stddef.h>

typedef struct {
    size_t lineNumber;
    char const * functionName;
    char const * fileName;
} allocation_meta_data_t;

allocation_meta_data_t * allocation_meta_data_new(size_t lineNumber, char const * functionName, char const * fileName);

void allocation_meta_data_destroy(allocation_meta_data_t ** metaData);

#endif