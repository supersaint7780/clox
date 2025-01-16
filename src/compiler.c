#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char* source) {
    initScanner(source);
    size_t line = -1;

    for(;;) {
        Token token = scanToken();
        if(token.line != line) {
            printf("%4zu ", token.line);
            line = token.line;
        } else {
            printf("   | ");
        }

        // *s allows passing precision as arguments
        // we print token.length characters starting from token.start
        printf("%2d '%.*s'\n", token.type, token.length, token.start);

        if(token.type == TOKEN_EOF) {
            break;
        } 
    }

}
