#include "hashtable.h"
#include <string.h>
#include <stdlib.h>

void ht_init(hash_table *table) {
    for(int i = 0; i < TABLE_SIZE; i++){
        table->buckets[i] = NULL;
    }
}

unsigned int hash(const char *key) {
    unsigned int hash = 5381;
    int c;
    while((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
}

void ht_insert(hash_table *table, const char *key, int value) {
    unsigned int indx = hash(key);
    struct Node* current = table->buckets[indx];
    while(current != NULL) {
        if(strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    struct Node* new_node = malloc(sizeof(struct Node));
    if(new_node == NULL) return;
    
    new_node->value = value;
    strncpy(new_node->key, key, sizeof(new_node->key) - 1);
    new_node->next = table->buckets[indx];
    table->buckets[indx] = new_node;
}

int *ht_search(hash_table *table, const char *key) {
    unsigned int indx = hash(key);
    struct Node* current = table->buckets[indx];
    while(current != NULL) {
        if(strcmp(current->key, key) == 0) {
            return &current->value;
        }
        current = current->next;
    }
    return NULL;
}

void ht_clear(hash_table *table) {
   for(int i = 0; i < TABLE_SIZE; i++) {
        struct Node* current = table->buckets[i];
        while(current != NULL) {
            struct Node* new_node = current->next;
            free(current);
            current = new_node;
        }
        table->buckets[i] = NULL;
   } 
}
