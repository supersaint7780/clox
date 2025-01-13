#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
size_t disassembleInstruction(Chunk* chunk, size_t offset);

#endif