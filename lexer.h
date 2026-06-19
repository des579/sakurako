#ifndef LEXER_H
#define LEXER_H

#define LEXER_EXPRESSION_FINISHED -100 /* means end of expression */

#include "str.h"

enum type_e {
    TYPE_UNDEFINED,            // for error handling
    TYPE_WHITESPACE,           // ' ' and '\n'

    TYPE_IDENTIFIER,           // names that aren't built-in

    TYPE_VAR, TYPE_FUNCTION,

    TYPE_LPAREN, TYPE_RPAREN,  // ()
    TYPE_LBRACK, TYPE_RBRACK,  // []
    TYPE_LBRACE, TYPE_RBRACE,  // {}

    TYPE_SEMICOLON,       // ; <- end of line

    TYPE_COMMA, TYPE_COLON,    // , ;
    TYPE_ASSIGN,          // =
};

struct lexer_s {
    char* expression;
    size_t expression_length;
    size_t cpos;
};

struct token_s {
    string_t* str;         // used only if .type == IDENTIFIER
    enum type_e type;
};

typedef struct lexer_s lexer_t;
typedef struct token_s token_t;

lexer_t* init_lexer(char* expression, size_t expression_length);
token_t* next_token(lexer_t* lexer);

int free_lexer(lexer_t* lexer);
int free_token(token_t* token);

#endif // LEXER_H
