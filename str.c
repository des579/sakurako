#include <stdlib.h>
#include <stdio.h>

#include "str.h"
#include "retcodes.h"

string_t* init_str() {
    string_t* new = calloc(1, sizeof(string_t));
    
    new->data = malloc(STR_BLOCK_SIZE * sizeof(char));
    new->data[0] = '\0';
    new->size = STR_BLOCK_SIZE;

    return new;
}

int free_str(string_t* string) {
    if (string->data)
        free(string->data);
    free(string);
}

int strappend(string_t* str, char c) {
    if (!str || c == '\0')
        return -1; // TODO: make some better error handling i guess

    if (str->size == str->length) { // make the reallocation
        char* new = realloc(str->data, str->size + STR_BLOCK_SIZE);
        if (!new)
            return -1; // TODO: error handling pleaseeee

        str->data = new;
        str->size += STR_BLOCK_SIZE;
    }

    str->data[str->length] = c;
    str->length++;
    str->data[str->length] = '\0';

//     printf("append called...\n");
//     printf("new data: %s\n", str->data);
//     printf("new len: %llu\n", str->length);
//     printf("\n");

    return SUCCESS;
}

