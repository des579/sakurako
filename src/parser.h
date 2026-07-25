#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "lexer.h"
#include "vm.h"

class Parser {
protected:
    std::unique_ptr<std::vector<Instruction>> instructions;
public:
//     int parse_lexemes(std::vector<Lexem>* lexemes);
    std::vector<Instruction> get_instructions();
    Parser();
};

// std::vector<Instruction>* parse_lexemes(std::vector<Lexem>* lexemes);

#endif // PARSER_H
