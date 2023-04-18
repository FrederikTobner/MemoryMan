#include "pointer_table.h"

#if defined(MEM_DEBUG)

#include <stdint.h>

#define OFFSET_BASIS 0x811c9dc5u
#define PRIME        0x01000193u

static uint32_t fnv1a_hash_data(uint8_t const * data, size_t length) {
    uint32_t hash = OFFSET_BASIS;
    for (size_t i = 0; i < length; i++) {
        hash ^= data[i];
        hash *= PRIME;
    }
    return hash;
}

GENERATE_TABLE_FUNCTIONS(pointer_t, fnv1a_hash_data)

#endif