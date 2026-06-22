#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "vm.h"


int vm_run(v_m* vm) {
    if (!vm)
        return -1; // TODO: error handling

    vm->is_running = true;

    while(vm->is_running) {
        uint8_t operand = vm->code[vm->p_c];
        vm->p_c++;
        printf("%d\n", operand);

        switch(operand) {
            case HALT:
                vm->is_running = false;
                break;

            case PUSH_INT:
                int* int_data = (int*) &vm->code[vm->p_c];
                vm_push(int_data, sizeof(int), vm);
                break;


            case PRINT:
                printf("calling print\n");
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
        } // while is here

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


int vm_push(void* data, size_t size, v_m* vm) {
    memcpy(&vm->stack[vm->s_p], data, size);
    vm->s_p += size;
    return 0;
}


Value vm_pop(v_m* vm) {
    return vm->stack[--vm->s_p];
}


