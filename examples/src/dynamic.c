#include "dynamic.h"

int match(char pattern, char string) {
  if (pattern == string) {
    return 0;
  }
  else {
    return 1;
  }
}

int indel(char character) {
  return 1;
}

void print_matrix(Cell matrix[MAXSTRING+1][MAXSTRING+1]) {
  for (int y=0; y<=MAXSTRING; ++y) {
    for (int x=0; x<=MAXSTRING; ++x) {
      printf("%d ", matrix[x][y].value);
    }
    printf("\n");
  }
}

// pattern is y axis, target (string) is x axis
void approx_string_matching(char* pattern, char* string) {
  Cell matrix[MAXSTRING+1][MAXSTRING+1];
  int opt[3];

  // fill in base cases
  for (int i=0; i<=MAXSTRING; ++i) {
    matrix[0][i] = (Cell){i, -1};
    matrix[i][0] = (Cell){i, -1};
  }

  print_matrix(matrix);
  printf("\n");
  // populate matrix
  for (int y=1; y<=MAXSTRING; ++y) {
    for (int x=1; x<=MAXSTRING; ++x) {
      // find cost of options
      opt[MATCH] = matrix[x-1][y-1].value + match(pattern[y], string[x]);
      opt[INSERT] = matrix[x][y-1].value + indel(pattern[y]);
      opt[DELETE] = matrix[x-1][y].value + indel(string[x]);

      // find best option
      matrix[x][y].value = MAXSTRING;
      for (int i=0; i<3; ++i) {
        if (opt[i] < matrix[x][y].value) {
          printf("%d,%d val %d\n", x, y, opt[i]);
          matrix[x][y].value = opt[i];
          matrix[x][y].parent = i;
        }
      }
    }
  }

  print_matrix(matrix);
}

void example_dynamic(void) {
  printf("yee\n");
  approx_string_matching(" she", " the");
}
