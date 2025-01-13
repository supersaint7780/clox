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
    if (chunk->count >= chunk->capacity) {
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

void writeConstant(Chunk* chunk, Value value, size_t line) {
    size_t constantIndex = addConstant(chunk, value);
    if(constantIndex < 256) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, (uint8_t)constantIndex, line);
    } else {
        writeChunk(chunk, OP_CONSTANT_LONG, line);

        // writing the index as 24 bit number(big endian)
        writeChunk(chunk, (uint8_t)((constantIndex >> 16) & 0xff), line); // most significant byte
        writeChunk(chunk, (uint8_t)((constantIndex >> 8) & 0xff), line); // middle byte
        writeChunk(chunk, (uint8_t)(constantIndex & 0xff), line); // least significant byte
    }
}