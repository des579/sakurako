#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <charconv>
#include <cctype>

#include <stdio.h>

#include "lexer.h"

std::string TOKEN_CHARS = "{}()[]+-*/=;:\"',.!";

#define ISWHITECHAR(c) (c == ' ' || c == '\n' || c == '\0')
#define ISTOKENCHAR(c) (TOKEN_CHARS.find(c) != std::string::npos)

std::unordered_map<std::string, Token::Type> tokens = {
    {"{", Token::Type::LCURBRACK},
    {"}", Token::Type::RCURBRACK},
    {"[", Token::Type::LSQABRACK},
    {"]", Token::Type::RSQABRACK},
    {"(", Token::Type::LPAR},
    {")", Token::Type::RPAR},

    {"fun", Token::Type::FUNCTION},
    {"pub", Token::Type::PUB},
    {"int", Token::Type::INT},
    {"float", Token::Type::FLOAT},
    {"void", Token::Type::VOID},

    {"!", Token::Type::EXCL},

    {"+", Token::Type::PLUS},
    {"-", Token::Type::MINUS},
    {"*", Token::Type::STAR},
    {"/", Token::Type::SLASH},

    {":", Token::Type::COLON},
    {";", Token::Type::SEMICOLON},
    {">", Token::Type::GREATER},
};

Token::Type handle_number(std::string str) {
    Token::Type type = Token::Type::INUM;
    int dot_amount = 0;
    for (char c : str) {
        if (c == '.')
            dot_amount++;
        if (dot_amount > 1) {
            type = Token::Type::UNDEFINED;
            break;
        }
        
        if (!(c == '.' || isdigit(c))) {
            type = Token::Type::UNDEFINED;
            break;
        }
    }

    if (type != Token::Type::UNDEFINED) {
        if (dot_amount > 0)
            type = Token::Type::FNUM;
        else
            type == Token::Type::INUM;
    }


    return type;
}

std::string number_case(Lexer* lexer) {
    std::string res;
    char next = static_cast<char>(lexer->get_following());;
    res += static_cast<char>(lexer->current_char);

    while (isdigit(next) || next == '.') {
        lexer->advance();

        char c = static_cast<char>(lexer->current_char);
        next = static_cast<char>(lexer->get_following());
        
        res += c;
    }

    return res;
}

std::string string_case(Lexer* lexer) {
    std::string res;
    do {
        char c = static_cast<char>(lexer->current_char);
        res += c;

        lexer->advance();
    } while (lexer->current_char != '"' && lexer->current_char != EOF);
    res += static_cast<char>(lexer->current_char);

    return res;
}

Token Lexer::next_token() {
    Token token;
    token.type = Token::Type::EOFTOK;

    std::string token_str;

    int res = this->advance();
    while (res != EOF) {
        char next = static_cast<char>(this->get_following());
        char c = static_cast<char>(res);
        size_t token_str_size = token_str.size();
        
        if (token_str_size == 0 && isdigit(c)) {
            token_str = number_case(this);
            break;
        } else if (token_str_size == 0 && c == '"') {
            token_str = string_case(this);
            break;
        }

        // skip all white characters
        if (ISWHITECHAR(c) && token_str_size == 0) {
            res = this->advance();
            continue;
        }

        // the string should be empty
        if (ISTOKENCHAR(c) && token_str_size == 0) {
            token_str += c;
            break;
        }
        
        token_str += c;

        if (ISWHITECHAR(next) || ISTOKENCHAR(next))
            break;

        res = this->advance();
    }

    if (isdigit(token_str[0]))
        token.type = handle_number(token_str);
    else if (token_str[0] == '"') {
        token.type = Token::Type::STRING;
        token.value = token_str;
    } else if (res != EOF) {
        std::unordered_map<std::string, Token::Type>::iterator
            it = tokens.find(token_str);

        if (it != tokens.end())
            token.type = it->second;
        else 
            token.type = Token::Type::IDENTIFIER;
    }
    
    if (token.type == Token::Type::UNDEFINED)
        std::cout << "    error at line " << this->current_line << std::endl;
    else if (token.type == Token::Type::IDENTIFIER || token.type == Token::Type::STRING)
        token.value = token_str;

    std::cout << "token string  : " << token_str << std::endl;
    std::cout << "      type str: " << token_type_to_string(token.type) << std::endl;

    return token;
}



Lexer::Lexer(const char* filename) : current_line{0} {
    this->file.open(filename, std::ios::in);
}


int Lexer::advance() {
    this->current_char = this->file.get();
    if (this->current_char == '\n')
        this->current_line++;
    return this->current_char;
}

int Lexer::get_following() {
    return this->file.peek();
}

std::string token_type_to_string(Token::Type type) {
    switch (type) {
        case Token::Type::INUM: return "INUM";
        case Token::Type::FNUM: return "FNUM";

        case Token::Type::LCURBRACK: return "LCURBRACK";
        case Token::Type::RCURBRACK: return "RCURBRACK";
        case Token::Type::LSQABRACK: return "LSQABRACK";
        case Token::Type::RSQABRACK: return "RSQABRACK";
        case Token::Type::LPAR: return "LPAR";
        case Token::Type::RPAR: return "RPAR";

        case Token::Type::FUNCTION: return "FUNCTION";
        case Token::Type::PUB: return "PUB";

        case Token::Type::IF: return "IF";
        case Token::Type::FOR: return "FOR";
        case Token::Type::WHILE: return "WHILE";

        case Token::Type::INT: return "INT";
        case Token::Type::FLOAT: return "FLOAT";
        case Token::Type::VOID: return "VOID";

        case Token::Type::EXCL: return "EXCL";

        case Token::Type::STRQUOTE: return "STRQUOTE";
        case Token::Type::STRQUOTEWHATEVER: return "STRQUOTEWHATEVER";

        case Token::Type::COLON: return "COLON";
        case Token::Type::SEMICOLON: return "SEMICOLON";

        case Token::Type::PLUS: return "PLUS";
        case Token::Type::MINUS: return "MINUS";
        case Token::Type::STAR: return "STAR";
        case Token::Type::SLASH: return "SLASH";

        case Token::Type::GREATER: return "GREATER";

        case Token::Type::IDENTIFIER: return "IDENTIFIER";
        case Token::Type::STRING: return "STRING";

        case Token::Type::EOFTOK: return "EOFTOK";
        case Token::Type::UNDEFINED: return "UNDEFINED";
    }

    return "UNKNOWN";
}

