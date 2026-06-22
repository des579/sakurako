#ifndef VSTACK_H
#define VSTACK_H

#define VSTACK_OVERFLOW 5
#define VSTACK_POINTER_

#include <stdint.h>

struct vstack_s {
    uint8_t* s;
    int size;
    size_t sp;
};

typedef struct vstack_s vstack_t;

vstack_s* stack_init(size_t stack_size);
int stack_push(uint8_t val, vstack_t* stack);
int stack_pushn(void* data, unsigned int n, vstack_t* stack);
int stack_pop(uint8_t* dst, vstack_t* stack);
int stack_popn(void* dst, unsigned int n, vstack_t* stack);
int stack_free(vstack_t* stack);

#endif
