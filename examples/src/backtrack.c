#include "backtrack.h"

static void print_point(Point p) {
  printf("(%d, %d)", p.x, p.y);
}

int get_board(Point p, Board* b) {
  return b->grid[p.x][p.y];
}

void set_board(Point p, Board* b, int value) {
  b->grid[p.x][p.y] = value;

  if (value != 0) {
    ++b->filled;
  }
}

void del_board(Point p, Board* b) {
  if (b->grid[p.x][p.y] != 0) {
    b->grid[p.x][p.y] = 0;
    --b->filled;
  }
  else {
    printf("tried to delete blank point!\t");
    print_point(p);
    printf("\n");
    exit(EXIT_FAILURE);
  }
}

static void print_board(Board* b) {
  int value;

  for (int i=1; i<=DIMENSION; ++i) {
    for (int j=1; j<=DIMENSION; ++j) {
      value = b->grid[j][i];
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
  printf("found: %d\n", NCELLS - b->filled);
  printf("blank: %d\n", b->filled);
}

static Board* init_board(char* filename) {
  Board* new_board = malloc(sizeof(Board));

  new_board->filled = 0;
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

  for (int y=1; y<=DIMENSION; ++y) {
    for (int x=1; x<=DIMENSION; ++x) {
      value = fgetc(fp);
      if (value == '\n') {
        value = fgetc(fp);
      }

      // 48 is the acsii offset to its true value
      value -= 48;
      set_board((Point){x,y}, new_board, value);
    }
  }

  return new_board;
}



static void get_row(Point p, Point set[]) {
  for (int i=1; i<=DIMENSION; ++i) {
    set[i] = (Point){i, p.y};
  }
}

static void get_col(Point p, Point set[]) {
  for (int i=1; i<=DIMENSION; ++i) {
    set[i] = (Point){p.x, i};
  }
}

static int centre_val(int value) {
  int box_col = (value-1) / 3;
  return 2 + (3 * box_col);
}

static void get_box(Point p, Point set[]) {
  Point centre_point;

  centre_point.x = centre_val(p.x);
  centre_point.y = centre_val(p.y);

  int i=1;
  for (int j=centre_point.x-1; j<=centre_point.x+1; ++j) {
    for (int k=centre_point.y-1; k<=centre_point.y+1; ++k) {
      set[i] = (Point){k, j};
      ++i;
    }
  }
}
//
// void construct_candidates(Point p, Board* b) {
//   // return an array with possible values that could go in the given point
//   // keeping it simple with local check
// }
//
static bool is_complete(Board* b) {
  if (b->filled < 0) {
    printf("blanks has negitive value somehow\n");
    exit(EXIT_FAILURE);
  }

  return b->filled == 0;
}

static void possible_values(Point p, Board* b, bool possible[]) {
  Point sets[3][DIMENSION+1];
  int value;
  int x_val;
  int y_val;

  get_row(p, sets[0]);
  get_col(p, sets[1]);
  get_box(p, sets[2]);

  // initialise possible
  for (int i=1; i<=DIMENSION; ++i) {
    possible[i] = true;
  }

  for (int set=0; set<3; ++set) {
    for (int i=1; i<=DIMENSION; ++i) {
      x_val = sets[set][i].x;
      y_val = sets[set][i].y;
      value = b->grid[x_val][y_val];
      possible[value] = false;
    }
  }
}
//
// static void make_move(Board* b) {
//   // update the board and track the change
// }
//
// static void unmake_move(Board* b) {
//   // undo the most recent change and reverse the tracking
// }
//
// static void next_square(Board* b) {
//   // return the next square to be considered
//   // pick most constrained
// }
//
// void backtrack(int partial[], int step, Board* board) {
//   // int candidates[MCANDIDATES] = construct_candidates();
//   int nc = 0;
//
//   if (is_complete(board)) {
//     return;
//   }
//   
//   step += 1;
//   
// }

void example_backtrack(void) {
  Point pnt = {9,1};

  Point set[DIMENSION+1];
  get_row(pnt, set);
  get_col(pnt, set);
  get_box(pnt, set);

  for (int i=1; i<=DIMENSION; ++i) {
    // printf("i: %d\t centre: %d\n", i, centre_val(i));
    print_point(set[i]);
    printf("\n");
  }

  Board* b = init_board(INPUT_FILE);

  print_board(b);
  printf("board complete: %b\n", is_complete(b));

  printf("current: %d\n", b->grid[pnt.x][pnt.y]);
  bool possible[DIMENSION+1];
  possible_values(pnt , b, possible);
  for (int i=1; i<=DIMENSION; ++i) {
    printf("i: %d, valid: %d\n", i, possible[i]);
  }
}
