#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    // We increment the offset in the function rather in
    // loop because instruction can be of different sizes
    // disassembleInstruction returns the offset of the
    // next instruction
    for (size_t offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static size_t simpleInstruction(const char* name, size_t offset) {
    printf("%s\n", name);
    return offset + 1;
}

static size_t constantInstruction(const char* name, Chunk* chunk, size_t offset) {
    uint8_t constantIndex = chunk->code[offset + 1];
    printf("%-16s %4u '", name, constantIndex);
    printValue(chunk->constants.values[constantIndex]);
    printf("'\n");
    return offset + 2;
}

static size_t constantLongInstruction(const char* name, Chunk* chunk, size_t offset) {
    uint32_t constantIndex = (uint32_t)(chunk->code[offset + 1] << 16)
        | (uint32_t)(chunk->code[offset + 2] << 8)
        | (uint32_t)(chunk->code[offset + 3]);

    printf("%-16s %6u '", name, constantIndex);
    printValue(chunk->constants.values[constantIndex]);
    printf("'\n");
    return offset + 4;
}

size_t disassembleInstruction(Chunk* chunk, size_t offset) {
    // print the byte offset of the instruction 
    // to indicate its position in the chunk
    printf("%04zu ", offset);

    if (offset > 0 && getLineNumber(chunk, offset) == getLineNumber(chunk, offset - 1)) {
        printf("   | ");
    } else {
        printf("%4zu ", getLineNumber(chunk, offset));
    }


    uint8_t opcode = chunk->code[offset];
    switch (opcode) {
    case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_RETURN:
        return simpleInstruction("OP_RETURN", offset);
    case OP_CONSTANT_LONG:
        return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
    default:
        printf("Unknown opcode %d\n", opcode);
        return offset + 1;
    }
}