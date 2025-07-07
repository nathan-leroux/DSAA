#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <stdio.h>
#include <string.h>

#define MAXSTRING 9

// indexes for options
#define MATCH 0
#define INSERT 1
#define DELETE 2

typedef struct {
  int value;
  int parent;
} Cell;

void example_dynamic(void);

#endif
