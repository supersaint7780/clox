#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    initLineArray(&chunk->lines);
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, size_t line) {
    if (chunk->count <= chunk->capacity) {
        size_t oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(chunk->capacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
    writeLineArray(&chunk->lines, line);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeLineArray(&chunk->lines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

size_t addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);

    // Return the index where the constant was appended
    return chunk->constants.count - 1;
}

size_t getLineNumber(Chunk* chunk, size_t index) {
    size_t prefixCount = 0;
    for(size_t i = 0; i < chunk->lines.count; ++i) {
        prefixCount += chunk->lines.entries[i].count;
        if(index < prefixCount) {
            return chunk->lines.entries[i].lineNumber;
        }
    }
    return SIZE_MAX;
}