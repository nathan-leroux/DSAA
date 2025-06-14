#ifndef HASHING_H
#define HASHING_H

// define struct for bit array, not nessicary but eh
typedef struct {
  int size;
  int* array;
} Bitarray;

#define HASHTABLE_SIZE 16
#define K_SIZE 3

Bitarray* bitarray_init(int);
void bitarray_print(Bitarray*);
int bitarray_get(Bitarray*, int);
void bitarray_set(Bitarray*, int);
void example_hashing(void);
int bloom_add(Bitarray*, int[], char*);

#endif
