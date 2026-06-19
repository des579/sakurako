#include <stdio.h>
#include <string.h>

#include "lexer.h"

int main() {
    char* expression = "function a123() {\nprint(123)\n}";
    size_t expression_length = strlen(expression);
    lexer_t* lexer = init_lexer(expression, expression_length);

    token_t* token = next_token(lexer);
    printf("%llu\n", token->str->size);
    printf("%llu\n", token->str->length);
    printf("'%s'\n", token->str->data);

    free_token(token);
    free_lexer(lexer);

    return 0;
}


