#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define STACK_SIZE 256

typedef enum {
    VAL_BOOL, // true/false
    VAL_INT,    // for integers
    VAL_DOUBLE, // for double 
    VAL_STRING  // for strings
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


Value vm_pop(v_m* vm);
void vm_push(v_m* vm, Value val);
Value create_string(const char* ascii_text);
Value create_double(double val);
Value create_int(int64_t val);
Value create_bool(bool val);


typedef enum { 
    HALT,
    PUSH_INT,
    PUSH_BOOL,
    PUSH_STRING,
    PUSH_DOUBLE,
    ADD,
    PRINT
} Operand;

void vm_run(v_m* vm) {
vm->is_running = true;

while(vm->is_running) {
    uint8_t operand = vm->code[vm->p_c++];
        
    switch(operand) {
        
        case HALT:
            vm->is_running = false;
            break;
        case PUSH_INT: {
            int64_t val = *(int64_t*)&vm->code[vm->p_c];
            vm->p_c += sizeof(int64_t);
            vm_push(vm, create_int(val));
            break;
        }
        case PUSH_DOUBLE: {
            double val = *(double*)&vm->code[vm->p_c];
            vm->p_c += sizeof(double);
            vm_push(vm, create_double(val));
            break;
        }
        case PUSH_BOOL: {
            bool val = (bool)vm->code[vm->p_c++];
            vm_push(vm, create_bool(val));
            break;
        }
        case PUSH_STRING: {
            char* str = *(char**)&vm->code[vm->p_c];
            vm->p_c += sizeof(char*);
            vm_push(vm, create_string(str));
            break;
        }
        case ADD: {
            Value b = vm_pop(vm);
            Value a = vm_pop(vm);
            
            if(a.type == VAL_INT && b.type == VAL_INT) vm_push(vm, create_int(a.a_s.integer + b.a_s.integer));
            else if(a.type == VAL_INT && b.type == VAL_DOUBLE) vm_push(vm, create_double((double)a.a_s.integer + b.a_s.number));
            else if(a.type == VAL_DOUBLE && b.type == VAL_DOUBLE) vm_push(vm, create_double(a.a_s.number + b.a_s.number));
            else if(a.type == VAL_DOUBLE && b.type == VAL_INT) vm_push(vm, create_double(a.a_s.number + (double)b.a_s.number));
            else if(a.type == VAL_STRING && b.type == VAL_STRING) {
                size_t len = strlen(a.a_s.string) + strlen(b.a_s.string) + 1;
                char* new_str = malloc(len);
                strcpy(new_str, a.a_s.string);
                strcat(new_str, b.a_s.string);

                Value result = create_string(new_str);
                free(new_str);
                vm_push(vm, result);

                free(a.a_s.string);
                free(b.a_s.string);
            } else {
                printf("Types error. Can not add such types.\n");
                vm->is_running = false;
            }
            break;
        }
        case PRINT: {
            Value val = vm_pop(vm);
            switch(val.type) {                    
                case VAL_INT: 
                    printf("%lld\n", val.a_s.integer);
                    break;
                case VAL_DOUBLE:
                    printf("%f\n", val.a_s.number);
                    break;
                case VAL_BOOL:
                    printf("%s\n", val.a_s.boolean ? "true" : "false");
                    break;
                case VAL_STRING:
                    printf("%s\n", val.a_s.string);
                    free(val.a_s.string);
                break;
            }
            break; 
            }
        }        
    }
}


Value create_bool(bool val) {
    Value val_b;
    val_b.type = VAL_BOOL;
    val_b.a_s.boolean = val;
    return val_b;
}

Value create_int(int64_t val) {
    Value val_i;
    val_i.type = VAL_INT;
    val_i.a_s.integer = val;
    return val_i;
}

Value create_double(double val) {
    Value val_d;
    val_d.type = VAL_DOUBLE;
    val_d.a_s.number = val;
    return val_d;
}

Value create_string(const char* ascii_text) {
    Value val_s;
    val_s.type = VAL_STRING;
    val_s.a_s.string = strdup(ascii_text);
    return val_s;
}

void vm_push(v_m* vm, Value val) {
    vm->stack[vm->s_p++] = val;
}

Value vm_pop(v_m* vm) {
    return vm->stack[--vm->s_p];
}


