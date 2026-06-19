#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "lexer.h"
#include "retcodes.h"
#include "str.h"

static int lexer_getc(lexer_t* lexer, char* out);
static int lexer_getnext_nonwhite_c(lexer_t* lexer, char* out);

lexer_t* init_lexer(char* expression, size_t expression_length) {
    if (expression == NULL)
        return NULL;

    lexer_t* lexer = calloc(1, sizeof(lexer_t));
    char* exp = malloc(expression_length * sizeof(char));

    lexer->expression = exp;
    lexer->expression_length = expression_length;
    strncpy(lexer->expression, expression, expression_length);

    return lexer;
}

token_t* next_token(lexer_t* lexer) {
    if (lexer == NULL)
        return NULL;

    token_t* token = calloc(1, sizeof(token_t));
    string_t* str = init_str();
    token->str = str;

    char c;
    int getc_res;
    size_t index = 0;

    getc_res = lexer_getc(lexer, &c);

    while (c != ' ' && c != '\n'
            && getc_res != LEXER_EXPRESSION_FINISHED) {
        strappend(str, c);
        getc_res = lexer_getc(lexer, &c);
    } 


    return token;
}

int free_lexer(lexer_t* lexer) {
    free(lexer->expression);
    free(lexer);
    return SUCCESS;
}

int free_token(token_t* token) {
    if (token->str != NULL)
        free_str(token->str);
    free(token);
    return SUCCESS;
}

static int lexer_getc(lexer_t* lexer, char* out) {
    char o = lexer->expression[lexer->cpos];
    if (lexer->cpos == lexer->expression_length)
        return LEXER_EXPRESSION_FINISHED;

    lexer->cpos++;
    *out = o;
    return SUCCESS;
}

static int lexer_getnext_nonwhite_c(lexer_t* lexer, char* out) {
    size_t pos = lexer->cpos + 1;
    while (pos < lexer->expression_length && (lexer->expression[pos] != ' ' || lexer->expression[pos] != '\n'))
        pos++;

    if (pos == lexer->expression_length)
        return LEXER_EXPRESSION_FINISHED;
    
//     *out = lexer[pos];
    return SUCCESS;
}


