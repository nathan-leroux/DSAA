#include "partition.h"

static int max_cost(int val1, int val2) {
  if (val1 >= val2) {
    return val1;
  } else {
    return val2;
  }
}

void partition(Cell (*matrix)[PART_MAXSET], int* set, int set_n, int parts) {
  // partial sums
  int partials[set_n];
  partials[0] = set[0];
  for (int i = 1; i < set_n; ++i) {
    partials[i] = partials[i - 1] + set[i];
  }

  // x base case
  for (int x = 1; x <= parts; ++x) {
    matrix[x][0] = (Cell){set[0], -1};
  }

  // y base case
  for (int y = 1; y < set_n; ++y) {
    matrix[1][y] = (Cell){matrix[1][y - 1].value + set[y], -1};
  }

  // populate matrix
  int cost;
  for (int x = 2; x <= parts; ++x) {
    for (int y = 1; y < set_n; ++y) {
      matrix[x][y].value = PART_MAXCOST;
      for (int i = 0; i < y; ++i) {
        cost = max_cost(matrix[x - 1][i].value, partials[y] - partials[i]);

        if (matrix[x][y].value > cost) {
          matrix[x][y].value = cost;
          matrix[x][y].parent = i;
        }
      }
    }
  }
}

static void outcome_print(int* set, int start, int end) {
  printf("{ ");
  for (int i = start; i < end; ++i) {
    printf("%d ", set[i]);
  }
  printf("}");
}

void report_partitions(Cell (*matrix)[PART_MAXSET], int* set, int set_n,
                       int parts) {
  if (parts == 1) {
    outcome_print(set, 0, set_n + 1);
  } else {
    report_partitions(matrix, set, matrix[parts][set_n].parent, parts - 1);
    outcome_print(set, matrix[parts][set_n].parent + 1, set_n + 1);
  }
}

void print_partition(Cell (*matrix)[PART_MAXSET], int* set, int set_n,
                     int parts, bool parent) {
  // partition number
  printf("   ");
  for (int x = 1; x <= parts; ++x) {
    printf("%d ", x);
  }
  printf("\n");

  // set items
  for (int y = 1; y < set_n; ++y) {
    printf("%d ", set[y]);
    // matrix values
    for (int x = 1; x <= parts; ++x) {
      if (parent) {
        printf("%d ", matrix[x][y].parent);
      } else {
        printf("%d ", matrix[x][y].value);
      }
    }
    printf("\n");
  }
}

void example_partition(void) {
  int set[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int set_n = 9;
  int partitions = 3;
  Cell matrix[PART_MAXPARTS][PART_MAXSET];

  printf("\n");
  printf("Ordered Partition Problem\n");
  printf("set: {");
  for (int i = 0; i < set_n - 1; ++i) {
    printf("%d, ", set[i]);
  }
  printf("%d}\n", set[set_n - 1]);

  partition(matrix, set, set_n, partitions);
  print_partition(matrix, set, set_n, partitions, true);
  printf("\n");
  printf("partitions: ");
  report_partitions(matrix, set, set_n - 1, partitions);
  printf("\n");
}
