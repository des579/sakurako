#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <vector>
#include <memory>

struct Token {
    enum class Type {
        INUM, FNUM,             // both integer and float
        
        LCURBRACK, RCURBRACK,   // {}
        LSQABRACK, RSQABRACK,   // []
        LPAR, RPAR,             // ()
        
        FUNCTION,               // fun
        PUB,                    // pub

        IF,                     // if
        FOR, WHILE,             // for, while
        
        INT, FLOAT,             // int, float
        VOID,                   // void

        EXCL,                   // !

        STRQUOTE,               // "
        STRQUOTEWHATEVER,       // '
        
        COLON, SEMICOLON,       // :, ;

        PLUS, MINUS,            // +, -
        STAR, SLASH,            // *, /

        GREATER,                // >

        IDENTIFIER,             // just a name
        STRING,                 // the shit between ""

        EOFTOK,                 // to detect EOF
        UNDEFINED,              // errors and smth

    };
    
    Type type;

    // on which line the token is
    size_t line_number;

    // used when type is STRING, IDENTIFIER, NUMBER
    std::string value; 
};

class Lexer {
protected:
    std::fstream file;
    size_t current_line;

public:
    int current_char;

    int advance();
    int get_following();
    Token next_token();

    Lexer(const char* filename);
};

std::string token_type_to_string(Token::Type type);

#endif // LEXER_H
