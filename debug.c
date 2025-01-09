#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    // We increment the offset in the function rather in
    // loop because instruction can be of different sizes
    // disassembleInstruction returns the offset of the
    // next instruction
    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constantIndex = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constantIndex);
    printValue(chunk->constants.values[constantIndex]);
    printf("'\n");
    return offset + 2;
}

int disassembleInstruction(Chunk* chunk, int offset) {
    // print the byte offset of the instruction 
    // to indicate its position in the chunk
    printf("%04d ", offset);


    uint8_t opcode = chunk->code[offset];
    switch (opcode) {
    case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_RETURN:
        return simpleInstruction("OP_RETURN", offset);
    default:
        printf("Unknown opcode %d\n", opcode);
        return offset + 1;
    }
}