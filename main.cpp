#include <iostream>

#include "vm.h"

using namespace std;

int main() {
    VM vm;
    Instruction instruction1, instruction2, jmp_instruction;
    Value value;

    float f = 10001;

    value.type = Value::Type::PTR;
    value.ptr = &f;

    instruction1.opcode = Opcode::MV;
    instruction1.r1 = 0;
    instruction1.value = value;

    instruction2.opcode = Opcode::PRINT;
    instruction2.r1 = 0;

    jmp_instruction.opcode = Opcode::JMP;
    jmp_instruction.value.type = Value::Type::I64;
    jmp_instruction.value.i64 = 4;

    Instruction instructions[5];
    instructions[0] = instruction1;
    instructions[1] = instruction2;
    instructions[2] = jmp_instruction;
    instructions[4] = instruction2;

    vm.pc = 0;
    vm.execute(instructions, 5);

    return 0;
}

