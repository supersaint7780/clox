#ifndef CLOX_LINE_H
#define CLOX_LINE_H

#include "common.h"

// Run length encoding entry
typedef struct {
    size_t lineNumber;
    size_t count;
} LineEntry;

typedef struct {
    size_t count;
    size_t capacity;
    LineEntry* entries;
} LineArray;

void initLineArray(LineArray* array);
void writeLineArray(LineArray* array, size_t line);
void freeLineArray(LineArray* array);

#endif