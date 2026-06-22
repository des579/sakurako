#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stdbool.h>

#define STACK_SIZE 256

 

typedef enum {
    VAL_BOOL,
    VAL_INT,
    VAL_DOUBLE,
    VAL_STRING
} value_type;

typedef struct {
    value_type type;
    union {
        bool boolean;
        int64_t integer;
        double number;
        char* string;
    } a_s;
} Value;

typedef struct {
    // program
    uint8_t* code;
    int p_c;

    // stack
    Value stack[STACK_SIZE];
    int s_p;
    
    // vm state
    bool is_running;
} v_m;

typedef enum {
    HALT,
    PUSH_INT,
    PUSH_BOOL,
    PUSH_STRING,
    PUSH_DOUBLE,
    ADD,
    PRINT
} Operand;

 

Value create_string(const char* ascii_text);
Value create_double(double val);
Value create_int(int64_t val);
Value create_bool(bool val);
Value vm_pop(v_m* vm);

int vm_push(void* data, size_t size, v_m* vm);
int vm_run(v_m* vm);

#endif // VM_H
