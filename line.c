#include "line.h"
#include "memory.h"

void initLineArray(LineArray* array) {
    array->capacity = 0;
    array->count = 0;
    array->entries = NULL;
}
void writeLineArray(LineArray* array, size_t line) {
    if(array->capacity <= array->count) {
        size_t oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(array->capacity);
        array->entries = GROW_ARRAY(LineEntry, array->entries, oldCapacity, array->capacity);
    }

    if(array->count > 0 && line == array->entries[array->count - 1].lineNumber) {
        array->entries[array->count - 1].count += 1; 
    } else {
        LineEntry* entry = &array->entries[array->count++];
        entry->lineNumber = line;
        entry->count = 1;
    }
}
void freeLineArray(LineArray* array) {
    FREE_ARRAY(LineArray, array->entries, array->capacity);
    initLineArray(array);
}