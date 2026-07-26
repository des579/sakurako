#include <iostream>
#include <cstring>

#include "./src/vm.h"
#include "./src/lexer.h"

#include "./tests/lexer_test.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc >= 2 && std::strcmp(argv[1], "test") == 0) {
        printf("testing lexer...\n");
        lexer_test_general();
        return 0;
    }
    Lexer lexer("./examples/test.sak");

    Token tok = lexer.next_token();
    while (tok.type != Token::Type::EOFTOK) {
        tok = lexer.next_token();
    }

    return 0;
}
