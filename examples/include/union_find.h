#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdlib.h>
#include <stdio.h>


#define SET_SIZE 20

typedef struct {
  int root[SET_SIZE+1];
  int size[SET_SIZE+1];
  int set_size;
} UnionFind;

UnionFind* init_union_find(int size);
int find_uf(UnionFind* uf, int element);
void merge_uf(UnionFind* uf, int x, int y);

#endif
