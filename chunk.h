#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"

/*
* Each instruction will contain a one-byte operation code (opcode)
* It indicates the type of instruction e.g add, subtract.
*/
typedef enum {
    OP_RETURN, // Return from the current function
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code; 
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
void freeChunk(Chunk* chunk);


#endif