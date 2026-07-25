#include <iostream>
#include <cstring>

#include "vm.h"

#define SUCCESS 0
#define UNSUCCESSFUL_JUMP 1

#define DIFFERENT_TYPES_ERROR -1
#define THIS_TYPE_IS_NOT_ALLOWED -2

using namespace std;

int execute_instruction(Instruction* instruction, VM* vm);

int add_instruction(Value* a, Value* b, Value* res);
int sub_instruction(Value* a, Value* b, Value* res);
int mul_instruction(Value* a, Value* b, Value* res);
int div_instruction(Value* a, Value* b, Value* res);

const char* opcode_string(Opcode opcode);

void print_instruction(Instruction* instruction, VM* vm);
int jump_instruction(Instruction* instruction, VM* vm);
int jumpe_instruction(Instruction* instruction, VM* vm);
int jumpg_instruction(Instruction* instruction, VM* vm);
int jumpl_instruction(Instruction* instruction, VM* vm);

int VM::execute(vector<Instruction> instructions) {
    return 0;
}

int VM::execute(Instruction* instructions, size_t n) {
    if (this->pc >= n) return -1; // TODO

    for (size_t i = 0; i < n; i++) {
        if (this->pc >= n)
            break;

        Instruction* instruction = &instructions[this->pc];
        cout << "executing instruction: " << opcode_string(instruction->opcode) << " at " << this->pc << endl;
        if (execute_instruction(instruction, this) != SUCCESS)
            this->pc++;
    }

    return 0;
}

int execute_instruction(Instruction* instruction, VM* vm) {
    switch (instruction->opcode) {
        case Opcode::MV:
            vm->registers[instruction->r1] = instruction->value;
            break;

        case Opcode::ADD:
            add_instruction(&vm->registers[instruction->r1],
                            &vm->registers[instruction->r2],
                            &vm->registers[instruction->r3]);
            break;
            
        case Opcode::SUB:
            sub_instruction(&vm->registers[instruction->r1],
                            &vm->registers[instruction->r2],
                            &vm->registers[instruction->r3]);
            break;

        case Opcode::MUL:
            mul_instruction(&vm->registers[instruction->r1],
                            &vm->registers[instruction->r2],
                            &vm->registers[instruction->r3]);
            break;

        case Opcode::DIV:
            div_instruction(&vm->registers[instruction->r1],
                            &vm->registers[instruction->r2],
                            &vm->registers[instruction->r3]);
            break;

        case Opcode::PRINT:
            print_instruction(instruction, vm);
            break;

        case Opcode::JMP:
            if (jump_instruction(instruction, vm) == SUCCESS)
                return SUCCESS;
            break;

        case Opcode::JMPE:
            if (jumpe_instruction(instruction, vm) == SUCCESS)
                return SUCCESS;
            break;

        case Opcode::JMPG:
            if (jumpg_instruction(instruction, vm) == SUCCESS)
                return SUCCESS;
            break;

        case Opcode::JMPL:
            if (jumpl_instruction(instruction, vm) == SUCCESS)
                return SUCCESS;
            break;
    }

    return 0;
}

int jump_instruction(Instruction* instruction, VM* vm) {
    vm->pc = instruction->value.i64;
    return 0;
}

int jumpg_instruction(Instruction* instruction, VM* vm) {
    Value vr1 = vm->registers[instruction->r1];
    Value vr2 = vm->registers[instruction->r2];

    if (vr1.type != vr2.type)
        return DIFFERENT_TYPES_ERROR;

    switch (vr1.type) {
        case Value::Type::I64:
            if (vr1.i64 > vr2.i64) {
                vm->pc = instruction->value.i64; 
                return SUCCESS;
            }
            break;

        case Value::Type::F64:
            if (vr1.f64 > vr2.f64) {
                vm->pc = instruction->value.i64;
                return SUCCESS;
            }
            break;
    }

    return 1;
}

int jumpl_instruction(Instruction* instruction, VM* vm) {
    Value vr1 = vm->registers[instruction->r1];
    Value vr2 = vm->registers[instruction->r2];

    if (vr1.type != vr2.type)
        return DIFFERENT_TYPES_ERROR;

    switch (vr1.type) {
        case Value::Type::I64:
            if (vr1.i64 < vr2.i64) {
                vm->pc = instruction->value.i64; 
                return SUCCESS;
            }
            break;

        case Value::Type::F64:
            if (vr1.f64 < vr2.f64) {
                vm->pc = instruction->value.i64;
                return SUCCESS;
            }
            break;
    }

    return 1;
}

int jumpe_instruction(Instruction* instruction, VM* vm) {
    Value vr1 = vm->registers[instruction->r1];
    Value vr2 = vm->registers[instruction->r2];

    if (vr1.type != vr2.type)
        return DIFFERENT_TYPES_ERROR;

    switch (vr1.type) {
        case Value::Type::I64:
            if (vr1.i64 == vr2.i64) {
                vm->pc = instruction->value.i64; 
                return SUCCESS;
            }
            break;

        case Value::Type::F64:
            if (vr1.f64 == vr2.f64) {
                vm->pc = instruction->value.i64;
                return SUCCESS;
            }
            break;
    }

    return 1;
}



void print_instruction(Instruction* instruction, VM* vm) {
    Value* v = &vm->registers[instruction->r1];
    switch (v->type) {
        case Value::Type::I64:
            cout << v->i64 << endl;
            break;
        case Value::Type::F64:
            cout << v->f64 << endl;
            break;
    }
}

int add_instruction(Value* a, Value* b, Value* res) {
    if (a->type == Value::Type::PTR || b->type == Value::Type::PTR)
        return THIS_TYPE_IS_NOT_ALLOWED;
    else if (a->type != b->type)
        return DIFFERENT_TYPES_ERROR;

    if (a->type == Value::Type::I64) {
        res->i64 = a->i64 + b->i64;
        res->type = Value::Type::I64;
    } else {
        res->f64 = a->f64 + b->f64;
        res->type = Value::Type::F64;
    }

    return SUCCESS;
}

int sub_instruction(Value* a, Value* b, Value* res) {
    if (a->type == Value::Type::PTR || b->type == Value::Type::PTR)
        return THIS_TYPE_IS_NOT_ALLOWED;
    else if (a->type != b->type)
        return DIFFERENT_TYPES_ERROR;

    if (a->type == Value::Type::I64) {
        res->i64 = a->i64 - b->i64;
        res->type = Value::Type::I64;
    } else {
        res->f64 = a->f64 - b->f64;
        res->type = Value::Type::F64;
    }

    return SUCCESS;
}


int mul_instruction(Value* a, Value* b, Value* res) {
    if (a->type == Value::Type::PTR || b->type == Value::Type::PTR)
        return THIS_TYPE_IS_NOT_ALLOWED;
    else if (a->type != b->type)
        return DIFFERENT_TYPES_ERROR;

    if (a->type == Value::Type::I64) {
        res->i64 = a->i64 * b->i64;
        res->type = Value::Type::I64;
    } else {
        res->f64 = a->f64 * b->f64;
        res->type = Value::Type::F64;
    }

    return SUCCESS;
}


int div_instruction(Value* a, Value* b, Value* res) {
    if (a->type == Value::Type::PTR || b->type == Value::Type::PTR)
        return THIS_TYPE_IS_NOT_ALLOWED;
    else if (a->type != b->type)
        return DIFFERENT_TYPES_ERROR;

    if (a->type == Value::Type::I64) {
        res->i64 = a->i64 / b->i64;
        res->type = Value::Type::I64;
    } else {
        res->f64 = a->f64 / b->f64;
        res->type = Value::Type::F64;
    }

    return SUCCESS;
}

const char* opcode_string(Opcode opcode) {
    switch (opcode) {
        case Opcode::ADD:   return "ADD";
        case Opcode::SUB:   return "SUB";
        case Opcode::MUL:   return "MUL";
        case Opcode::DIV:   return "DIV";
        case Opcode::MV:    return "MV";
        case Opcode::JMP:    return "JMP";
        case Opcode::PRINT: return "PRINT";
        default:            return "UNKNOWN";
    }
}



