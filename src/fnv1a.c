#include "fnv1a.h"

#define OFFSET_BASIS 0x811c9dc5u
#define PRIME        0x01000193u

uint32_t fnv1a_hash_data(uint64_t data, size_t length) {
    uint32_t hash = OFFSET_BASIS;
    for (size_t i = 0; i < length; i++) {
        hash ^= (data >> (8 * i)) & 0xff;
        hash *= PRIME;
    }
    return hash;
}