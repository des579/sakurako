#include <iostream>
#include <fstream>

#include <stdio.h> // the c++ std::cout is shit

#include "../src/lexer.h"

void lexer_test_general() {
    std::ifstream ifile("tests/scripts/lexer_general_test.sak");
    if (!ifile.is_open()) {
        printf("couldn't open the tests/scripts/lexer_general_test.sak file\n");
        return;
    }
    ifile.close();

    Lexer lexer("tests/scripts/lexer_general_test.sak");

    std::vector<Token::Type> expected_types = {
        Token::Type::INUM,
        Token::Type::FNUM,
        Token::Type::LCURBRACK,
        Token::Type::RCURBRACK,
        Token::Type::LSQABRACK,
        Token::Type::RSQABRACK,
        Token::Type::LPAR,
        Token::Type::RPAR,
        Token::Type::PUB,
        Token::Type::FUNCTION,
        Token::Type::IDENTIFIER,
        Token::Type::MINUS,
        Token::Type::PLUS,
        Token::Type::STAR,
        Token::Type::SLASH,
        Token::Type::EQUALS,
        Token::Type::GREATER,
        Token::Type::COLON,
        Token::Type::DOT, 
        Token::Type::EXCL,
        Token::Type::INT,
        Token::Type::FLOAT,
        Token::Type::VOID,
        Token::Type::STRING
    };

    size_t current_token = 0;
    size_t tests_passed = 0;
    Token token = lexer.next_token();
    while (token.type != Token::Type::EOFTOK) {
        if (current_token >= expected_types.size()) {
            printf("file size is not the same as expected_types size\n");
            break;
        }
        Token::Type type = expected_types.at(current_token);
        if (type != token.type) {
            printf("expected type: %s but got %s\n",
                    token_type_to_string(type).c_str(),
                    token_type_to_string(token.type).c_str());
        } else
            tests_passed++;

        token = lexer.next_token();
        current_token++;
    }

    printf("general test passed %llu/%llu\n", tests_passed, expected_types.size());
}

