#include <stdlib.h>
#include <stdio.h>

#include "vstack.h"

vstack_s* stack_init(int stack_size) {
    vstack_t* stack = malloc(sizeof(vstack_t)); // TODO: error handling
    stack->s = malloc(stack_size * sizeof(uint8_t));
    stack->sp = 0;
    stack->size = stack_size;
    return stack;
}


int stack_push(uint8_t val, vstack_t* stack) {
    if (!stack)
        return -1; // TODO: error handling

    stack->s[stack->sp] = val;
    stack->sp++;
    return 0;
}

int stack_pushn(void* data, unsigned int n, vstack_t* stack) {
    if (!stack)
        return -1; // TODO: error handling

    memcpy(stack->s[stack->sp], data, n);
    stack->sp+=n;
    return 0;
}

int stack_pop(uint8_t* dst, vstack_t* stack) {
    if (!stack)
        return -1; // TODO: error handling

    *dst = stack->s[stack->sp];
    stack->sp--;
    return 0;
}

int stack_popn(void* dst, unsigned int n, vstack_t* stack) {
    if (!stack)
        return -1; // TODO: error handling

    memcpy(dst, stack->s[stack->sp], n);
    stack->sp-=n;
    return 0;
}

int stack_free(vstack_t* stack) {
    if (!stack)
        return -1; // TODO: error handling

    free(stack->s);
    free(stack);
    return 0;
}

