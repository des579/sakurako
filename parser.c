#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "parser.h"
#include "str.h"
#include "retcodes.h"

bytecode_t* create_bytecode(token_t* tokens, size_t size) {
    if (!tokens)
        return NULL;
    bytecode_t* bytecode = calloc(1, sizeof(bytecode_t));
    string_t* str = init_str();

    return bytecode;
}

int free_bytecode(bytecode_t* bytecode) {
    if (!bytecode)
        return -1; // TODO: do some better error handling

    free_str(bytecode->data);
    free(bytecode);

    return SUCCESS;
}

