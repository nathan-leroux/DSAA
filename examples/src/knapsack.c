#include "knapsack.h"

int col_size(int value) {
  int columns = 0;

  // always true
  while (value >= 0) {
    ++columns;
    value /= 10;
    
    if (value == 0) {
      break;
    }
  }

  return columns;
}

void col_char(char value, char* buffer, int buffer_size) {
  buffer[0] = value;

  for (int i=1; i<buffer_size; ++i) {
    buffer[i] = ' ';
  }
}

// this implementation is fucked, i got no idea whats going on
// re-think when you have some brain cells

void col_int(int value, char* buffer, int buffer_size) {
  int value_size = col_size(value);

  for (int i=value_size-1; i>=0; --i) {
    // 48 is ascii offset for '0'
    buffer[i] = (value % 10) + 48;
    value /= 10;
  }

  for (int i=value_size; i<buffer_size; ++i) {
    buffer[i] = ' ';
  }
}


void print_subset(Cell matrix[MAXN][MAXSET],int* set, int set_n, int total) {
  int buffer_size = col_size(MAXN);
  char* col_buffer = malloc(sizeof(char)*(buffer_size+1));
  col_buffer[buffer_size] = '\0';

  // top row index
  printf("      ");
  for (int x=0; x<=total; ++x) {
    col_int(x, col_buffer, buffer_size);
    printf("%s ", col_buffer);
  }
  printf("\n");

  // set index
  for (int y=1; y<=set_n; ++y) {
    col_char(y+48, col_buffer, buffer_size);
    printf("%s ", col_buffer);
    col_int(set[y-1], col_buffer, buffer_size);
    printf("%s ", col_buffer);

    for (int x=0; x<=total; ++x) {
      col_char(matrix[x][y].value, col_buffer, buffer_size);
      printf("%s ", col_buffer);
    }
    printf("\n");
  }
  printf("\n");
}

void report_subset(Cell (*matrix)[MAXSET], int* set, int y, int total) {
  if (total == 0) {
    printf("\n");
    return;
  }
  if (matrix[total][y].parent == -1) {
    report_subset(matrix, set, y-1, total);
  }
  else {
    printf("%d ", set[y-1]);
    report_subset(matrix, set, y-1, matrix[total][y].parent);
  }
}


void subset_sum(Cell (*matrix)[MAXSET], int* set, int set_n, int total) {
  matrix[0][0] = (Cell){'T', -1};

  for (int x=1; x<=MAXN; ++x) {
    matrix[x][0] = (Cell){'F', -1};
  }

  for (int y=1; y<=set_n; ++y) {
    for (int x=0; x<=total; ++x) {
      matrix[x][y].value = matrix[x][y-1].value;
      matrix[x][y].parent = -1;

      if ((x >= set[y-1]) && (matrix[x-set[y-1]][y-1].value == 'T')) {
        matrix[x][y].value = 'T';
        matrix[x][y].parent = x-set[y-1];
      }
    }
  }
}

void example_knapsack(void) {
  int set[5] = {1,2,4,8,16};
  int set_n = 5;
  int total = 29;
  Cell matrix[MAXN][MAXSET];

  subset_sum(matrix, set, set_n, total);

  print_subset(matrix, set, set_n, total);
  printf("\n");
  report_subset(matrix, set, set_n, total);
}

