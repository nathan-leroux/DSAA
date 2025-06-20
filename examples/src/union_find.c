#include "union_find.h"

UnionFind* init_union_find(int set_size) {
  UnionFind* new_uf = malloc(sizeof(UnionFind));

  for (int i=1; i<=set_size; ++i) {
    new_uf->root[i] = i;
    new_uf->size[i] = 1;
  }
  new_uf->set_size = set_size;

  return new_uf;
}

int find_uf(UnionFind* uf, int element) {
  if (uf->root[element] == element) {
    return element;
  }

  return find_uf(uf, uf->root[element]);
}

void merge_uf(UnionFind* uf, int x, int y) {
  int root_x = find_uf(uf, x);
  int root_y = find_uf(uf, y);

  if (root_x == root_y) {
    printf("trying to merge connected component: %d %d\n", x, y);
    return;
  }

  if (uf->size[root_x] >= uf->size[root_y]) {
    uf->root[root_y] = root_x;
    uf->size[root_x] += root_y;
  }
  else {
    uf->root[root_x] = root_y;
    uf->size[root_y] += root_x;
  }
}
