#include "hashing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
hash(char* string, int random)
{
  long hash = 0;
  long constant = 4483;

  for (int i = 0; i < strlen(string); ++i) {
    hash += string[i] * (constant << i);
  }

  return (hash % random) % HASHTABLE_SIZE;
}

static int
rolling_hash(char* string, int length)
{
  if (strlen(string) == 0) {
    return 0;
  }

  int hash = string[0];
  int constant = 256;
  int modulus = 101;
  int power = length;

  for (int i = 1; i < length; ++i) {
    power--;

    if (power > 0) {
      hash *= constant;
      hash %= modulus;
    }

    hash += string[i];
    hash %= modulus;
  }

  return hash;
}

static int
update_hash(int hash, char new, char old, int len)
{
  int constant = 256;
  int modulus = 101;

  // negative value avoider
  hash += modulus;

  // remove old char
  int removed_hash = old;
  for (int i = 0; i < len - 1; ++i) {
    removed_hash *= constant;
    removed_hash %= modulus;
  }
  hash -= removed_hash;

  // base shift
  hash *= constant;

  // add new char
  hash = (hash + new) % modulus;

  return hash;
}

int
explicit_check(char* string, char* substring)
{
  for (int i = 0; i < strlen(substring); ++i) {
    if (string[i] != substring[i]) {
      return 0;
    }
  }

  return 1;
}

void
bitarray_print(Bitarray* array)
{
  for (int i = 0; i < array->size; ++i) {
    printf("%d", bitarray_get(array, i));

    if (i % 8 == 7) {
      printf(" ");
    }
  }
  printf("\n");
}

int
bitarray_get(Bitarray* array, int index)
{
  size_t int_size = sizeof(int) * 8;
  int element = index / int_size;
  int bit = index % int_size;

  return (array->array[element] >> bit) & 1;
}

void
bitarray_set(Bitarray* array, int index)
{
  size_t int_size = sizeof(int) * 8;
  int element = index / int_size;
  int bit = index % int_size;

  if (index >= HASHTABLE_SIZE) {
    return;
  }

  array->array[element] = array->array[element] | (1 << bit);
}

Bitarray*
bitarray_init(int size)
{
  Bitarray* new_array = malloc(sizeof(Bitarray));

  size_t int_size = sizeof(int) * 8;

  int ints_required = size / int_size;
  if (size % int_size != 0) {
    ++ints_required;
  }

  printf("bytes req: %ld\n", ints_required * sizeof(int));
  new_array->size = size;
  new_array->array = calloc(sizeof(char), ints_required);

  return new_array;
}

int
bloom_add(Bitarray* array, int* rn, char* string)
{
  // define 3 random numbers
  int bucket;
  int new = 0;

  printf("Adding: %s\n", string);

  for (int i = 0; i < K_SIZE; ++i) {
    bucket = hash(string, rn[i]);

    if (bitarray_get(array, bucket) == 0) {
      new = 1;
    }
    bitarray_set(array, bucket);
  }

  return new;
}

int
rabin_karp(char* string, char* substring)
{
  // hash the substring
  int length = strlen(substring);
  int subhash = rolling_hash(substring, length);
  int hash = rolling_hash(string, length);
  char last_char = string[0];

  // printf("indexes: ");

  if (subhash == hash) {
    printf("0 ");
  }

  // printf("string: %s, sub: %s\n", string, substring);

  for (int i = 1; i <= (strlen(string) - length); ++i) {
    // printf("i: %d, new: %c, old: %c\n", i, string[i+length-1], last_char);

    hash = update_hash(hash, string[i + length - 1], last_char, length);
    last_char = string[i];

    if (hash == subhash && explicit_check(&string[i], substring)) {
      printf("i: %d\n", i);
      // return i;
    }
  }

  printf("\n");
  return -1;
}

void
example_hashing(void)
{
  Bitarray* new = bitarray_init(HASHTABLE_SIZE);
  int randoms[K_SIZE];

  for (int i = 0; i < K_SIZE; ++i) {
    // big enough random number
    randoms[i] = 1117 + (rand() % 1283);
  }

  printf("##\n");
  printf("## Adding words to Bloom Filter\n");
  printf("##\n");
  bloom_add(new, randoms, "this");
  bitarray_print(new);
  bloom_add(new, randoms, "is");
  bitarray_print(new);
  bloom_add(new, randoms, "a");
  bitarray_print(new);
  bloom_add(new, randoms, "word");
  bitarray_print(new);

  printf("##\n");
  printf("## Checking if \'word\' is in\n");
  printf("##\n");

  if (bloom_add(new, randoms, "word") == 0) {
    printf("word is in!\n");
  }

  printf("##\n");
  printf("## Checking if \'notaword\' is in\n");
  printf("##\n");

  if (bloom_add(new, randoms, "notaword") == 0) {
    printf("notaword is in!\n");
  }
  printf("##\n");
  printf("## Rabin-Karp String Searching\n");
  printf("##\n");

  char* string = "dabcabcabcababcabbaabc";
  char* substring = "abc";

  printf("string: %s\nsubstring: %s\n", string, substring);
  rabin_karp(string, substring);
}
