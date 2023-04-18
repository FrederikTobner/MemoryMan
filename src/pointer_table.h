#ifndef POINTER_TABLE_H_
#define POINTER_TABLE_H_

#if defined(MEM_DEBUG)

#include "table.h"

#include <stddef.h>

typedef void * pointer_t;

GENERATE_TABLE_ENTRY_TYPE(pointer_t)

GENERATE_TABLE_TYPE(pointer_t)

GENERATE_TABLE_PROTOTYPES(pointer_t)

#endif

#endif /* POINTER_TABLE_H_ */