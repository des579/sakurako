#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "lexer.h"
#include "retcodes.h"
#include "str.h"

static int lexer_getc(lexer_t* lexer, char* out);
static int lexer_getnextc(lexer_t* lexer, char* out);
static int is_breaking_char(char c);
static enum type_e get_type(char *expression);

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
    // TODO: check for allocations, if there is NULL or no
    token->str = str;

    char nextc;
    char c;
    int nextc_res;
    int c_res;

    do {
        nextc_res = lexer_getnextc(lexer, &nextc);
        c_res = lexer_getc(lexer, &c);
        if (c_res == LEXER_EXPRESSION_FINISHED)
            break;

        if ((c == ' ' || c == '\n') && str->length == 0)
            continue;
        
        strappend(str, c);
        if ((is_breaking_char(nextc) && str->length != 0) || is_breaking_char(c))
            break;
    } while (nextc_res != LEXER_EXPRESSION_FINISHED);

    token->type = get_type(str->data);
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

static enum type_e get_type(char *expression) {
    if (!expression || expression[0] == '\0')
        return TYPE_UNDEFINED;

    if (strcmp(expression, "function") == 0)
        return TYPE_FUNCTION;

    if (strcmp(expression, "var") == 0)
        return TYPE_VAR;

    if (expression[1] == '\0') {
        switch (expression[0]) {
            case ' ': case '\n':
                return TYPE_WHITESPACE;
            case '(':
                return TYPE_LPAREN;
            case ')':
                return TYPE_RPAREN;
            case '[':
                return TYPE_LBRACK;
            case ']':
                return TYPE_RBRACK;
            case '{':
                return TYPE_LBRACE;
            case '}':
                return TYPE_RBRACE;
            case ';':
                return TYPE_SEMICOLON;
            case ',':
                return TYPE_COMMA;
            case ':':
                return TYPE_COLON;
            case '=':
                return TYPE_ASSIGN;
        }
    }

    return TYPE_IDENTIFIER;
}

static int lexer_getc(lexer_t* lexer, char* out) {
    if (lexer->cpos >= lexer->expression_length)
        return LEXER_EXPRESSION_FINISHED;
    *out = lexer->expression[lexer->cpos];
    lexer->cpos++;
    return SUCCESS;
}

static int is_breaking_char(char c) {
    switch (c) {
        case '{':
        case '}':
        case '[':
        case ']':
        case '(':
        case ')':
        case '=':
        case ',':
        case ';':
        case ':':
        case ' ':
        case '\n':
            return 1;
        default:
            return 0;
    }
}
static int lexer_getnextc(lexer_t* lexer, char* out) {
    size_t pos = lexer->cpos + 1;

    if (pos >= lexer->expression_length)
        return LEXER_EXPRESSION_FINISHED;
    
    *out = lexer->expression[pos];
    return SUCCESS;
}


