#ifndef MEMORY_MAN_FNVIA_H_
#define MEMORY_MAN_FNVIA_H_

#include <stddef.h>
#include <stdint.h>

uint32_t fnv1a_hash_data(uint64_t data, size_t length);

#endif
