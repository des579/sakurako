#include <fstream>
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <cstring>
#include <string>

#include "sakas.h"

static int validate_label(string label);
static int process_instruction(string* line, unordered_map<string, int>* labels, Instruction* instruction);

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
    while (getline(input, line)) {
        cout << line << endl;

        
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
    
            labels[label] = line_number;
        } else {
            Instruction instruction;
            process_instruction(&line, &labels, &instruction);
        }

        line_number++;
    }

    return instructions;
}

static int process_instruction(string* line, unordered_map<string, int>* labels, Instruction* instruction) {
    string l = line->erase(0, line->find_first_not_of(" \t\n\r\f\v"));
    string op = l.substr(0, l.find(' '));

    cout << op << endl;

    return 0;
}

static int validate_label(string label) {
    cout << "validate_label " << label << endl;
    cout << "----------------" << endl;
    if (isdigit(label[0]))
        return -1; // TODO: possibly better error handling
    for (char c : label) {
        if (!isalnum(static_cast<unsigned char>(c)))
            return -1; // TODO: possibly better error handling
    }

    return 0;
}

