#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

Scanner scanner;

void initScanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z')
        || ch == '_';
}

static int isAtEnd() {
    return *scanner.current == '\0';
}

static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.line = scanner.line;
    token.length = (int)(scanner.current - scanner.start);
    return token;
}

static Token errorToken(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.line = scanner.line;
    token.start = message;
    token.length = (int)strlen(message);
    return token;
}

static char advance() {
    return *scanner.current++;
}

static char peek() {
    return *scanner.current;
}

static char peekNext() {
    if (isAtEnd()) {
        return '\0';
    }
    return scanner.current[1];
}

static bool match(char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (peek() != expected) {
        return false;
    }
    advance();
    return true;
}

// for skipping whitespace and comments before scanning a token
static void skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n': {
            scanner.line++;
            advance();
            break;
        }
        case '/': {
            if (peekNext() == '/') {
                while (peek() != '\n' || !isAtEnd()) {
                    advance();
                }
            } else {
                return;
            }
            break;
        }
        default:
            return;
        }
    }
}

static Token string() {
    while (peek() != '"' || !isAtEnd()) {
        if (peek() == '\n') {
            scanner.line++;
        }
        advance();
    }

    if (isAtEnd()) {
        return errorToken("Unterminated String.");
    }

    // the closing quote
    advance();
    return makeToken(TOKEN_STRING);
}

static Token number() {
    while (isDigit(peek())) {
        advance();
    }

    // checking for fractional part
    if (peek() == '.' && isDigit(peekNext())) {
        // consume the '.'
        advance();
        while (isDigit(peek())) {
            advance();
        }
    }

    return makeToken(TOKEN_NUMBER);
}

static TokenType checkKeyword(int start, int restLength, const char* rest, TokenType type) {
    if (scanner.current - scanner.start == start + restLength
        && memcmp(scanner.start + start, rest, restLength)) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
    switch (scanner.start[0]) {
    case 'a': return checkKeyword(1, 2, "nd", TOKEN_AND);
    case 'c': return checkKeyword(1, 4, "lass", TOKEN_CLASS);
    case 'e': return checkKeyword(1, 3, "lse", TOKEN_ELSE);
    case 'i': return checkKeyword(1, 1, "f", TOKEN_IF);
    case 'n': return checkKeyword(1, 2, "il", TOKEN_NIL);
    case 'o': return checkKeyword(1, 1, "r", TOKEN_OR);
    case 'p': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
    case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
    case 's': return checkKeyword(1, 4, "uper", TOKEN_SUPER);
    case 'v': return checkKeyword(1, 2, "ar", TOKEN_VAR);
    case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
    case 'f': {
        if (scanner.current - scanner.start > 1) {
            switch (scanner.start[1]) {
            case 'a': return checkKeyword(2, 3, "lse", TOKEN_FALSE);
            case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
            case 'u': return checkKeyword(2, 1, "n", TOKEN_FUN);
            }
        }
        break;
    }
    case 't': {
        if (scanner.current - scanner.start > 1) {
            switch (scanner.start[1]) {
            case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
            case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
            }
        }
        break;
    }
    }
    return TOKEN_IDENTIFIER;
}

static Token identifier() {
    while (isAlpha(peek()) || isDigit(peek())) {
        advance();
    }
    return makeToken(identifierType());
}

Token scanToken() {
    skipWhitespace();
    scanner.start = scanner.current;

    if (isAtEnd()) {
        return makeToken(TOKEN_EOF);
    }

    char c = advance();
    if (isAlpha(c)) {
        return identifier();
    }
    if (isDigit(c)) {
        return number();
    }

    switch (c) {
    case '(': return makeToken(TOKEN_LEFT_PAREN);
    case ')': return makeToken(TOKEN_RIGHT_PAREN);
    case '{': return makeToken(TOKEN_RIGHT_BRACE);
    case '}': return makeToken(TOKEN_RIGHT_BRACE);
    case ';': return makeToken(TOKEN_SEMICOLON);
    case '.': return makeToken(TOKEN_DOT);
    case ',': return makeToken(TOKEN_COMMA);
    case '-': return makeToken(TOKEN_MINUS);
    case '+': return makeToken(TOKEN_PLUS);
    case '/': return makeToken(TOKEN_SLASH);
    case '*': return makeToken(TOKEN_STAR);
    case '!': return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=': return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<': return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>': return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    case '"': return string();
    }

    return errorToken("Unexpected character.");
}