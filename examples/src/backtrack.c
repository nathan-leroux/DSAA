#include "backtrack.h"

static Board* init_board(char* filename) {
  Board* new_board = malloc(sizeof(Board));

  new_board->blanks = NCELLS;
  for (int i=0; i<=NCELLS; ++i) {
    new_board->moves[i].x = 0;
    new_board->moves[i].y = 0;
  }

  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("couldn't open file %s\n", filename);
    exit(EXIT_FAILURE);
  }

  int value;

  for (int i=1; i<=DIMENSION; ++i) {
    for (int j=1; j<=DIMENSION; ++j) {
      value = fgetc(fp);
      if (value == '\n') {
        value = fgetc(fp);
      }

      // 48 is the acsii offset to its true value
      value -= 48;

      printf("%d\n", value);
      new_board->grid[i][j] = value;
      if (value != 0) {
        --new_board->blanks;
      }
    }
  }

  return new_board;
}

void print_board(Board* b) {
  int value;

  for (int i=1; i<=DIMENSION; ++i) {
    for (int j=1; j<=DIMENSION; ++j) {
      value = b->grid[i][j];
      if (value == 0) {
        printf("_ ");
      }
      else {
        printf("%d ", value);
      }
      if (j%3 == 0) {
        printf("  ");
      }
    }
    printf("\n");
    if (i%3 == 0) {
      printf("\n");
    }
  }
}

void example_backtrack(void) {
  Board* b = init_board(INPUT_FILE);

  printf("yee\n");

  print_board(b);
  printf("blank: %d\n", b->blanks);
}
