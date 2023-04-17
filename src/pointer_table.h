#ifndef POINTER_TABLE_H_
#define POINTER_TABLE_H_

#include "table.h"

#include <stddef.h>

typedef void *pointer;

GENERATE_TABLE_ENTRY_TYPE(pointer)

GENERATE_TABLE_TYPE(pointer)

GENERATE_TABLE_PROTOTYPES(pointer)

#endif /* POINTER_TABLE_H_ */