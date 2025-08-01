#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "sudoku_board.txt"

#define DIMENSION 9
#define NCELLS DIMENSION* DIMENSION
#define MCANDIDATES 9

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  int grid[DIMENSION + 1][DIMENSION + 1];
  int filled;
  int move_count;
  Point moves[NCELLS + 1];
} Board;

void example_backtrack(void);

#endif
