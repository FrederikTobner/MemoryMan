#include "allocation_meta_data.h"

#include "untraced_allocations.h"

allocation_meta_data_t * allocation_meta_data_new(size_t lineNumber, char const * functionName, char const * fileName) {
    allocation_meta_data_t * metaData = untraced_malloc(sizeof(allocation_meta_data_t));
    if (!metaData) {
        return NULL;
    }
    metaData->lineNumber = lineNumber;
    metaData->functionName = functionName;
    metaData->fileName = fileName;
    return metaData;
}

void allocation_meta_data_destroy(allocation_meta_data_t ** metaData) {
    if (metaData && *metaData) {
        untraced_free(*metaData);
        *metaData = NULL;
    }
}