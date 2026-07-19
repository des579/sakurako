#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <cstring>
#include <string>
#include <algorithm>

#include "sakas.h"

static int validate_label(string label);
static int process_instruction(string* line, unordered_map<string, int>* labels, Instruction* instruction);
static int get_instruction(Instruction* instruction, string params);
static Opcode get_opcode(string* op);

using namespace std;

// the instruction can be in format
// label
//  func1:
//
// instruction
//  mv 1, r10
//  print r10
//  jmp label
vector<Instruction>* parse_file(string filename) {
    ifstream input(filename);
    if (!input) return NULL;

    unordered_map<string, int> labels;

    vector<Instruction>* instructions = new vector<Instruction>;

    string line;
    unsigned int line_number = 1;
    unsigned int instruction_counter = 0;
    while (getline(input, line)) {
//         cout << line << endl;

        
        if (line.find(":") != string::npos) {
            string line_no_whites;
            for (char c : line) {
                if (!isspace(static_cast<unsigned char>(c)))
                    line_no_whites += c;
            }
            string label = line_no_whites.substr(0, line_no_whites.size() - 1); // removing the :

            if (validate_label(label) < 0) {
                cout << "label error 1..." << endl;
                break; // error or smth
            }

            if (labels.find(label) != labels.end()) {
                cout << "label error 2..." << endl;
                break; // compile error, but do not stop compiling
            }
    
            labels[label] = instruction_counter;
        } else {
            Instruction instruction;
            process_instruction(&line, &labels, &instruction);
            instruction_counter++;
        }

        line_number++;
    }

    return instructions;
}

static int process_instruction(string* line, unordered_map<string, int>* labels, Instruction* instruction) {
    string l = line->erase(0, line->find_first_not_of(" \t\n\r\f\v"));
    string op = l.substr(0, l.find(' ')); // the opcode part, e.g. mv
    Opcode opcode = get_opcode(&op);


    string params = l.substr(l.find(' ') + 1);
    erase_if(params, [](char c) {return c == ' ';});

    cout << op << ' ' << params << endl;

    return 0;
}

static int get_instruction(Instruction* instruction, string params) {
    if (params.size() == 0)
        ; // TODO: error, the size cant be 0

    vector<string> tokens;
    string current;
    for (char c : params) {
        static bool in_string;
        if (c == '"')
            in_string = !in_string;

        if (c == ',' && !in_string) {
            tokens.push_back(current);
            current.clear();
        }
        else
            current += c;
    }


    vector<string>::iterator it;
    for (it = tokens.begin(); it != tokens.end(); ++it) {
        // can be string, number (int or float), register
        char* d = it->data();
        if (d[0] == '\0')
            ; // error, the params is "r1,,r4" or smth
        else if (d[0] == '"')
            ; // is a string
        else if (d[0] == 'r')
            ; // register
        else if (isdigit(d[0]))
            ; // number
        else
            ; // error
    }

    return 0;
}

static Opcode get_opcode(string* op) {
    static unordered_map<std::string, Opcode> opcodes = {
        {"add",   Opcode::ADD},
        {"sub",   Opcode::SUB},
        {"mul",   Opcode::MUL},
        {"div",   Opcode::DIV},
        {"mv",    Opcode::MV},
        {"print", Opcode::PRINT},
        {"jmp",   Opcode::JMP},
        {"jmpg",  Opcode::JMPG},
        {"jmpe",  Opcode::JMPE},
        {"jmpl",  Opcode::JMPL},
    };

    Opcode opcode;
    unordered_map<string, Opcode>::iterator it = opcodes.find(*op);

    if (it != opcodes.end())
        opcode = it->second;
    else
        opcode = Opcode::UNDEFINED;
    

    return opcode;
}

static int validate_label(string label) {
    if (isdigit(label[0]))
        return -1; // TODO: possibly better error handling
    for (char c : label) {
        if (!isalnum(static_cast<unsigned char>(c)))
            return -1; // TODO: possibly better error handling
    }

    return 0;
}

