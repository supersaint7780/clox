#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "vm.h"
#include "scanner.h"

typedef struct {
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;


// precedence are in the order from lowest to highest
typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT, // =
    PREC_OR,         // or 
    PREC_AND,        // and
    PREC_EQUALITY,   // ==, !=
    PREC_COMPARISON, // <=, <, >=, >
    PREC_TERM,       // + , -
    PREC_FACTOR,     // * , /
    PREC_UNARY,      // !, -
    PREC_CALL,        // . () []
    PREC_PRIMARY,
} Precedence;

typedef void (*ParseFn) ();

typedef struct {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
} ParseRule;

bool compile(const char* source, Chunk* chunk);

#endif 