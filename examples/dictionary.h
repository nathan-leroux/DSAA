#ifndef DICTIONARY_H
#define DICTIONARY_H

// a sufficiently large prime number
#define TABLE_SIZE 23021


typedef struct {
    struct bucket* data[TABLE_SIZE];
} Dictionary;

struct bucket {
    char* key;
    int value;
    struct bucket* next;
    struct bucket* prev;
};


Dictionary* dict_init(void);
struct bucket* dict_search(Dictionary*, char*);
void dict_insert(Dictionary*, char* , int);
void dict_delete(Dictionary*, struct bucket*);
void example_dictionary(void);

#endif
