#include <stdio.h>
#include <string.h>

#include "lexer.h"

int main() {
    char* expression = "function a123(param1: int) {\nprint(123);\n}";
    size_t expression_length = strlen(expression);
    lexer_t* lexer = init_lexer(expression, expression_length);

    for (int i = 0; i < 12; i++) {
        token_t* token = next_token(lexer);
        if (token->type != TYPE_UNDEFINED)
            printf("token->data: '%s'\n", token->str->data);
        else
            printf("no token\n");
        free_token(token);
    }

    free_lexer(lexer);

    return 0;
}


