#include <stdio.h>

#include "vm.h"
#include "debug.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}
void freeVM() {}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
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
        case OP_RETURN: {
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
        }
        }
    }
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}