#if defined(MEM_DEBUG)

#include "pointer_table.h"
#include "untraced_memory.h"
#include <stdio.h>

static pointer_t_table_t * pointer_table = NULL;
void memory_man_init(void) {
    printf("Initializing Table\n");
    pointer_table = untraced_malloc(sizeof(pointer_t_table_t));
    pointer_t_table_init_table(pointer_table);
    printf("Initialized Table\n");
}

#endif