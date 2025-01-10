#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"
#include "line.h"

/*
* INSTRUCTION FORMAT:
* Each instruction will contain a one-byte operation code (opcode)
* It indicates the type of instruction e.g add, subtract.
* instruction may contain operands after opcode called
* bytecode instruction operands. Low level notation that
* modify how the bytecode instruction behaves
* 
* The opcode determines the number of operand bytes it has
* and their meadning.
* Example: a simple instruction like "return" may have no operands
* whereas instructins like "load variable" need an operand to know
* which variable to load
*/
typedef enum {
    // Opcode to load a constant. It takes a single byte operand
    // which specifies which constant to load from the chunk's 
    // constant array
    OP_CONSTANT, 

    OP_RETURN, // Return from the current function
} OpCode;

/*
* Many instruction sets store value directly in the code stream
* right after the code. These are called immediate instructions.
* For variable sized constants like string this does not work.
* They are stored in a separate "constant data" region. The 
* instruction to load the constant has an (operand) address/offset
* pointing to where the value is stored in that section.
*
* For immediate instructions we also need to deal with alignment
* padding and endianees. So instead for simplicty we put all
* constant in the constant pool. Here ValueArray, each chunk has 
* one.
*/

typedef struct {
    size_t count;
    size_t capacity;
    uint8_t* code; // bytecode array
    LineArray lines; // stores position of each byte in the code
    ValueArray constants; // constant pool
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, size_t line);
void freeChunk(Chunk* chunk);
size_t addConstant(Chunk* chunk, Value value);
size_t getLineNumber(Chunk* chunk, size_t index);


#endif