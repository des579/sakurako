#include <iostream>

#include "vm.h"
#include "lexer.h"

using namespace std;

int main() {
    Lexer lexer("./examples/test.sak");

    Token tok = lexer.next_token();
    while (tok.type != Token::Type::EOFTOK) {
        tok = lexer.next_token();
    }

    return 0;
}
