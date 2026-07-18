#include <iostream>
#include <cstring>

#include "vm.h"

#define JMP_INSTRUCTION_SUCCESS 2

using namespace std;

int execute_instruction(Instruction* instruction, VM* vm);

int add_instruction(Value* a, Value* b, Value* res);
int sub_instruction(Value* a, Value* b, Value* res);
int mul_instruction(Value* a, Value* b, Value* res);
int div_instruction(Value* a, Value* b, Value* res);

const char* opcodeToString(Opcode opcode);

void print_instruction(Instruction* instruction, VM* vm);
int jump_instruction(Instruction* instruction, VM* vm);
int jumpe_instruction(Instruction* instruction, VM* vm);
int jumpg_instruction(Instruction* instruction, VM* vm);
int jumpl_instruction(Instruction* instruction, VM* vm);

int VM::execute(Instruction* instructions, size_t n) {
    if (this->pc >= n) return -1; // TODO

    for (size_t i = 0; i < n; i++) {
        if (this->pc >= n)
            break;

        Instruction* instruction = &instructions[this->pc];
        cout << "executing instruction: " << opcodeToString(instruction->opcode) << " at " << this->pc << endl;
        if (execute_instruction(instruction, this) != JMP_INSTRUCTION_SUCCESS)
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
            if (jump_instruction(instruction, vm) == 0)
                return JMP_INSTRUCTION_SUCCESS;
            break;

        case Opcode::JMPE:
            if (jumpe_instruction(instruction, vm) == 0)
                return JMP_INSTRUCTION_SUCCESS;
            break;

        case Opcode::JMPG:
            if (jumpg_instruction(instruction, vm) == 0)
                return JMP_INSTRUCTION_SUCCESS;
            break;

        case Opcode::JMPL:
            if (jumpl_instruction(instruction, vm) == 0)
                return JMP_INSTRUCTION_SUCCESS;
            break;
    }

    return 0;
}

int jump_instruction(Instruction* instruction, VM* vm) {
    if (instruction->value.type != Value::Type::I64) {
        cout << "execute_instruction Opcode::JMP: can't jump on non-int value" << endl;
        return -1; // TODO
    } else if (instruction->value.i64 < 0) {
        cout << "can't jump on negative value" << endl;
        return -1; // TODO
    }

    vm->pc = instruction->value.i64;
    return 0;
}

int jumpg_instruction(Instruction* instruction, VM* vm) {
    if (instruction->value.type != Value::Type::I64) {
        cout << "execute_instruction Opcode::JMP: can't jump on non-int value" << endl;
        return -1; // TODO
    } else if (instruction->value.i64 < 0) {
        cout << "can't jump on negative value" << endl;
        return -1; // TODO
    }

    Value vr1 = vm->registers[instruction->r1];
    Value vr2 = vm->registers[instruction->r2];

    if (vr1.type != vr2.type)
        return -1; // TODO

    switch (vr1.type) {
        case Value::Type::I64:
            if (vr1.i64 > vr2.i64)
                vm->pc = instruction->value.i64;
            return 0;

        case Value::Type::F64:
            if (vr1.f64 > vr2.f64)
                vm->pc = instruction->value.i64;
            return 0;
    }

    return 1;
}

int jumpl_instruction(Instruction* instruction, VM* vm) {
    if (instruction->value.type != Value::Type::I64) {
        cout << "execute_instruction Opcode::JMP: can't jump on non-int value" << endl;
        return -1; // TODO
    } else if (instruction->value.i64 < 0) {
        cout << "can't jump on negative value" << endl;
        return -1; // TODO
    }

    Value vr1 = vm->registers[instruction->r1];
    Value vr2 = vm->registers[instruction->r2];

    if (vr1.type != vr2.type)
        return -1; // TODO

    switch (vr1.type) {
        case Value::Type::I64:
            if (vr1.i64 < vr2.i64)
                vm->pc = instruction->value.i64;
            return 0;

        case Value::Type::F64:
            if (vr1.f64 < vr2.f64)
                vm->pc = instruction->value.i64;
            return 0;
    }

    return 1;
}

int jumpe_instruction(Instruction* instruction, VM* vm) {
    if (instruction->value.type != Value::Type::I64) {
        cout << "execute_instruction Opcode::JMP: can't jump on non-int value" << endl;
        return -1; // TODO
    } else if (instruction->value.i64 < 0) {
        cout << "can't jump on negative value" << endl;
        return -1; // TODO
    }

    Value vr1 = vm->registers[instruction->r1];
    Value vr2 = vm->registers[instruction->r2];

    if (vr1.type != vr2.type)
        return -1; // TODO

    switch (vr1.type) {
        case Value::Type::I64:
            if (vr1.i64 == vr2.i64)
                vm->pc = instruction->value.i64;
            return 0;

        case Value::Type::F64:
            if (vr1.f64 == vr2.f64)
                vm->pc = instruction->value.i64;
            return 0;
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
        case Value::Type::PTR:
            cout << v->ptr << endl;
            break;
    }
}

int add_instruction(Value* a, Value* b, Value* res) {
    if (a->type == Value::Type::PTR || b->type == Value::Type::PTR || res->type == Value::Type::PTR)
        return -1; // TODO: better error handling
    else if (a->type != b->type)
        return -1; // TODO

    if (a->type == Value::Type::I64)
        res->i64 = a->i64 + b->i64;
    else
        res->f64 = a->f64 + b->f64;

    return 0;
}

int sub_instruction(Value* a, Value* b, Value* res) {
    if (a->type == Value::Type::PTR || b->type == Value::Type::PTR || res->type == Value::Type::PTR)
        return -1; // TODO: better error handling
    else if (a->type != b->type)
        return -1; // TODO

    if (a->type == Value::Type::I64)
        res->i64 = a->i64 - b->i64;
    else
        res->f64 = a->f64 - b->f64;

    return 0;
}


int mul_instruction(Value* a, Value* b, Value* res) {
    if (a->type == Value::Type::PTR || b->type == Value::Type::PTR || res->type == Value::Type::PTR)
        return -1; // TODO: better error handling
    else if (a->type != b->type)
        return -1; // TODO

    if (a->type == Value::Type::I64)
        res->i64 = a->i64 * b->i64;
    else
        res->f64 = a->f64 * b->f64;

    return 0;
}


int div_instruction(Value* a, Value* b, Value* res) {
    if (a->type == Value::Type::PTR || b->type == Value::Type::PTR || res->type == Value::Type::PTR)
        return -1; // TODO: better error handling
    else if (a->type != b->type)
        return -1; // TODO

    if (a->type == Value::Type::I64)
        res->i64 = a->i64 / b->i64;
    else
        res->f64 = a->f64 / b->f64;

    return 0;
}

const char* opcodeToString(Opcode opcode) {
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



