#include <stdlib.h>

#include "memory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        pointer = NULL;
        return pointer;
    }

    void* temp = realloc(pointer, newSize);
    if (temp == NULL) {
        pointer = NULL;
        exit(15);
    }
    pointer = temp;
    return pointer;
}