#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

/*
* Each instruction will contain a one-byte operation code (opcode)
* It indicates the type of instruction e.g add, subtract.
*/
typedef enum {
    OP_RETURN, // Return from the current function
} OpCode;

/*
* Many instruction sets store value directly in the code stream
* right after the code. These are called immediate instructions.
* For variable sized constants like string this does not work.
* They are stored in a separate "constant data" region. The 
* instruction to load the constant has an address/offset pointing
* to where the value is stored in that section.
*
* For immediate instructions we also need to deal with alignment
* padding and endianees. So instead for simplicty we put all
* constant in the constant pool. Here ValueArray, each chunk has 
* one.
*/

typedef struct {
    int count;
    int capacity;
    uint8_t* code; // bytecode array
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);


#endif