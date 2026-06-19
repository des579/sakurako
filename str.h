#ifndef STR_H
#define STR_H

#define STR_BLOCK_SIZE 32

struct string_s {
    char* data;
    size_t size;     // the actual size of the string
    size_t length;   // amount of chars before '\0'
};

typedef struct string_s string_t;

string_t* init_str();
int free_str(string_t* string);

// automatically appends at end and reallocs if needed
int strappend(string_t* str, char c);

#endif // STR_H
