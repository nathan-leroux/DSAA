#include "dictionary.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Dictionary example
 *
 * dict_init      - O(1)
 * dict_insert    - O(1)
 * dict_search    - O(1)  (expected case)
 * dict_delete    - O(1)
 *
 * if the table was small and keys hashed in a way where they were not
 * uniformly distributed, multiple keys may end up in the same bucket.
 * although this would be incredibly unlikely,
 * it would make search() possibly O(n)
 *
 */

// an implementation of a polynomial rolling hash function
int hash(char* key) {
  long hash = 0;
  long constant = 31;

  for (int i = 0; i < strlen(key); ++i) {
    hash += key[i] * pow(constant, i);
  }

  return hash % TABLE_SIZE;
}

Dictionary* dict_init(void) {
  Dictionary* new_htable = malloc(sizeof(Dictionary));

  return new_htable;
}

void dict_insert(Dictionary* htable, char* key, int value) {
  struct bucket* new_bucket = malloc(sizeof(struct bucket));
  struct bucket* existing_bucket = htable->data[hash(key)];

  new_bucket->key = key;
  new_bucket->value = value;
  new_bucket->next = existing_bucket;
  new_bucket->prev = NULL;

  if (existing_bucket != NULL) {
    existing_bucket->prev = new_bucket;
  }

  htable->data[hash(key)] = new_bucket;
}

struct bucket* dict_search(Dictionary* htable, char* key) {
  int index = hash(key);
  struct bucket* selected = htable->data[index];

  while (selected != NULL) {
    if (selected->key == key) {
      return selected;
    } else {
      selected = selected->next;
    }
  }

  return NULL;
}

void dict_delete(Dictionary* htable, struct bucket* selected) {
  if (selected->prev != NULL) {
    selected->prev->next = selected->next;
  } else {
    // if previous is NULL, it is connected to the hashtable
    htable->data[hash(selected->key)] = selected->next;
  }

  if (selected->next != NULL) {
    selected->next->prev = selected->prev;
  }
}

void example_dictionary(void) {
  Dictionary* table = dict_init();

  printf("## Dictionary\n\n");
  printf("Appending to table\n");

  dict_insert(table, "one", 1);
  printf("insert- key: \"one\", value: 1\n");
  dict_insert(table, "two", 2);
  printf("insert- key: \"two\", value: 2\n");
  dict_insert(table, "three", 3);
  printf("insert- key: \"three\", value: 3\n");

  printf("\n");
  printf("Searching dictionary\n");

  struct bucket* selected = dict_search(table, "one");
  printf("key: %s, val: %d\n", selected->key, selected->value);

  printf("\n");
  printf("Deleting from dictionary\n");

  dict_delete(table, selected);
  if (dict_search(table, "one") == NULL) {
    printf("searched for 'one', not found\n");
  }
}
