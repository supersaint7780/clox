#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "value.h"

#define INITIAL_STACK_SIZE 256

typedef struct {
    // chunk being executed
    Chunk* chunk;

    // keeps track of the location of instruction
    // that is about to be executed
    // ip: instruction pointer
    uint8_t* ip; 
    size_t stackCapacity;
    Value* stack;
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif