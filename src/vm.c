#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "debug.h"
#include "compiler.h"
#include "memory.h"

VM vm;

static void initStack() {
    vm.stackCapacity = INITIAL_STACK_SIZE;
    vm.stack = GROW_ARRAY(Value, vm.stack, 0, vm.stackCapacity);
    vm.stackTop = vm.stack;
}

static void freeStack() {
    FREE_ARRAY(Value, vm.stack, vm.stackCapacity);
}

void initVM() {
    initStack();
}
void freeVM() {
    freeStack();
}

void push(Value value) {
    if ((size_t)(vm.stackTop - vm.stack) == vm.stackCapacity) {
        size_t oldCapacity = vm.stackCapacity;
        vm.stackCapacity = GROW_CAPACITY(oldCapacity);
        vm.stack = GROW_ARRAY(Value, vm.stack, oldCapacity, vm.stackCapacity);
    }
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    if(vm.stackTop == vm.stack) {
        exit(1);
    }
    vm.stackTop--;
    return *vm.stackTop;
}

uint8_t readByte() {
    return *vm.ip++;
}

Value readConstant() {
    return vm.chunk->constants.values[readByte()];
}

Value readConstantLong() {
    uint32_t byte1 = readByte() << 16;
    uint32_t byte2 = readByte() << 8;
    uint32_t byte3 = readByte();
    return vm.chunk->constants.values[(byte1 | byte2 | byte3)];
}

static InterpretResult run() {

#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while(false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("        ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[");
            printValue(*slot);
            printf("]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (size_t)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = readByte()) {
        case OP_CONSTANT: {
            Value constant = readConstant();
            push(constant);
            break;
        }
        case OP_CONSTANT_LONG: {
            Value constant = readConstantLong();
            push(constant);
            break;
        }
        case OP_NEGATE: {
            push(-pop());
            break;
        }
        case OP_RETURN: {
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
        }
        case OP_ADD: {
            BINARY_OP(+);
            break;
        }
        case OP_SUBTRACT: {
            BINARY_OP(-);
            break;
        }
        case OP_MULTIPLY: {
            BINARY_OP(*);
            break;
        }
        case OP_DIVIDE: {
            BINARY_OP(/ );
            break;
        }
        }
    }
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}