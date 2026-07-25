#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <vector>

using namespace std;

// r1, r2, r3, r4 are registers from Instruction
enum class Opcode {
    ADD,    // r1 = r2 + r3
    SUB,    // r1 = r2 - r3
    MUL,    // r1 = r2 * r3
    DIV,    // r1 = r2 / r3
    MV,     // val: any, r1
    PRINT,  // r1
    JMP,    // val: int
    JMPG,   // val: int, r1 > r2
    JMPE,   // val: int, r1 == r2
    JMPL,   // val: int, r1 < r2
    JMPR,   // r1: int


    UNDEFINED, // for error handling
};

struct Value {
    enum class Type {I64, F64, OBJTYPE, PTR};
    Type type;

    union {
        int64_t i64; // also used to get the object type
        double f64;
        void* ptr;
    };
};


// f.e. Opcode can be ADD: r1 is res, r2 is num1, r3 is num2
//      if it is ADD_OVERFLOW, then the r1 is the overflow bit
//      TODO: make the same work for multiplying
//            e.g. num1*num2 generates 128bit num, 
//            so divide in 2 registers
struct Instruction {
    Opcode opcode;

    Value value; // for MV instruction, e.g. mv val, register

    uint8_t r1;
    uint8_t r2;
    uint8_t r3;
    uint8_t r4;
};

class VM {
public:
    uint64_t pc;

    Value registers[20];

    int execute(Instruction* instructions, size_t n);
    int execute(vector<Instruction> instructions);
};

#endif // VM_H

