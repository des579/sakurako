#ifndef VM_H
#define VM_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    uint8_t* code;
    int p_c;
    Value stack[STACK_SIZE];
    int s_p;
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

 

Value vm_pop(v_m* vm);
void vm_push(v_m* vm, Value val);
Value create_string(const char* ascii_text);
Value create_double(double val);
Value create_int(int64_t val);
Value create_bool(bool val);
void vm_run(v_m* vm);

#endif    
