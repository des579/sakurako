#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "lexer.h"
#include "vm.h"

int main() {
    int64_t num1 = 101;
    double num2 = 12.23;

    size_t c_size = 1 + sizeof(int64_t) + 1 + sizeof(double) + 1 + 1 + 1;
    uint8_t* t_code = malloc(c_size);

    int idx = 0;

    t_code[idx++] = PUSH_DOUBLE;
    memcpy(&t_code[idx], &num1, sizeof(int64_t));
    idx += sizeof(int64_t);
    
    t_code[idx++] = PUSH_INT;
    memcpy(&t_code[idx], &num2, sizeof(double));
    idx += sizeof(double);

    t_code[idx++] = ADD;
    t_code[idx++] = PRINT;
    t_code[idx++] = HALT;

    v_m vm;
    vm.code = t_code;
    vm.p_c = 0;
    vm.s_p = 0;
    vm.is_running = false;

    printf("Launching VM...\n");
    vm_run(&vm);
    printf("VM Done...\n");

    return 0;
}


