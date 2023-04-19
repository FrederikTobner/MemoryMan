#include "memory_man.h"

#include <stdio.h>

void foo() {
    int * i = malloc(sizeof(int));
    // free(i);
}

int main(int argc, char const * argv[]) {
    printf("Hello World\n");
    foo();
    return 0;
}
