#ifndef SAKAS_H
#define SAKAS_H

#include <vector>
#include <string>

#include "vm.h"

using namespace std;

vector<Instruction>* parse_file(string filename);

#endif // SAKAS_H

