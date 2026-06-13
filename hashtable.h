#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#define TABLE_SIZE 128

typedef struct Node {
    char key[256];
    int value;
    struct Node *next;
} Node;

typedef struct {
    struct Node *buckets[TABLE_SIZE];
} hash_table;

void ht_init(hash_table *table);
void ht_insert(hash_table *table, const char *key, int value);
int *ht_search(hash_table *table, const char *key);
void ht_clear(hash_table *table);
#endif // HASH_TABLE_H
