#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "str.h"

struct bytecode_s {
    string_t* data;
    size_t size;
};

typedef struct bytecode_s bytecode_t;

bytecode_t* create_bytecode(token_t* tokens, size_t size);

int free_bytecode(bytecode_t* bytecode);

#endif // PARSER_H
