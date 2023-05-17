#include <stdio.h>
#include <stdlib.h>

// The memory man include need to come after the stdlib include
#include "memory_tracer.h"

void foo() {
    int * i1 = malloc(sizeof(int));
    int * i2 = malloc(sizeof(int));
    int * i3 = malloc(sizeof(int));
    free(i1);
    // Memory leak !
    // free(i2);
    free(i3);
}

int main(int argc, char const ** argv) {
    printf("Hello World\n");
    foo();
    return 0;
}
