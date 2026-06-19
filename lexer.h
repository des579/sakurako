#ifndef LEXER_H
#define LEXER_H

#define LEXER_EXPRESSION_FINISHED -100 /* means end of expression */

#include "str.h"

enum type_e {
    IDENTIFIER,      // names that aren't built-in

    VAR, FUNCTION,

    LPAREN, RPAREN,  // ()
    LBRACK, RBRACK,  // []
    LBRACE, RBRACE,  // {}

    SEMICOLON,       // ; <- end of line

    COMMA, COLON,    // , ;
    ASSIGN,          // =
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
