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

void make_move(Point p, Board* b, int value) {
  set_board(p, b, value);
  b->moves[b->move_count] = p;
  ++b->move_count;
}

void unmake_move(Point p, Board* b) {
  --b->move_count;
  b->moves[b->move_count] = (Point){0,0};
  del_board(p, b);
}


static void print_board(Board* b) {
  int value;
  Point p;

  for (int y=1; y<=DIMENSION; ++y) {
    for (int x=1; x<=DIMENSION; ++x) {
      p = (Point){x,y};
      value = get_board(p, b);
      if (value == 0) {
        printf("_ ");
      }
      else {
        printf("%d ", value);
      }
      if (x%3 == 0) {
        printf("  ");
      }
    }
    printf("\n");
    if (y%3 == 0) {
      printf("\n");
    }
  }
  printf("blank: %d\n", NCELLS - b->filled);
  printf("found: %d\n", b->filled);
}

static Board* init_board(char* filename) {
  Board* new_board = malloc(sizeof(Board));

  new_board->filled = 0;
  new_board->move_count = 0;
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
      set[i] = (Point){j, k};
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
  if (b->filled > NCELLS) {
    printf("filled more than the max cells somehow\n");
    exit(EXIT_FAILURE);
  }

  return b->filled == NCELLS;
}

static void possible_values(Point p, Board* b, int possible[], int* npossible) {
  Point sets[3][DIMENSION+1];
  int value;
  Point check;
  bool vector[DIMENSION+1];

  get_row(p, sets[0]);
  get_col(p, sets[1]);
  get_box(p, sets[2]);

  // initialise possible
  for (int i=1; i<=DIMENSION; ++i) {
    vector[i] = true;
  }

  // make bool vector
  for (int set=0; set<3; ++set) {

    for (int i=1; i<=DIMENSION; ++i) {
      check.x = sets[set][i].x;
      check.y = sets[set][i].y;
      value = get_board(check, b);
      if (value != 0) {
        vector[value] = false;
      }
    }
  }

  for (int i=1; i<=DIMENSION; ++i) {
    if (vector[i]) {
      possible[*npossible] = i;
      ++(*npossible);
    }
  }
}

Point next_square_restricted(Board* b) {
  Point best_point = {0,0};
  Point current_point;
  int possible[MCANDIDATES+1];
  int least_options = MCANDIDATES;
  int current;

  for (int y=1; y<=DIMENSION; ++y) {
    for (int x=1; x<=DIMENSION; ++x) {
      current = 0;
      current_point = (Point){x,y};
      if (get_board(current_point, b) != 0) {
        continue;
      }

      possible_values(current_point, b, possible, &current);
      if (current < least_options) {
        best_point = current_point;
        least_options = current;
      }
    }
  }

  if (best_point.x == 0 || best_point.y == 0) {
    printf("couldn't find a point, is search already complete?\n");
    exit(EXIT_FAILURE);
  }

  return best_point;
}

Point next_square_simple(Board* b) {
  int value;
  Point p;
  // real simple, just pick the next available square
  for (int y=1; y<=DIMENSION; ++y) {
    for (int x=1; x<=DIMENSION; ++x) {
      p = (Point){x,y};
      value = get_board(p, b);
      if (value == 0) {
        return p;
      }
    }
  }

  printf("next_square couldn't find any emtpy! is the search already done?\n");
  exit(EXIT_FAILURE);
}

void backtrack(Board* board, int* calls, bool simple_search) {
  ++(*calls);

  if (is_complete(board)) {
    return;
  }

  int candidates[MCANDIDATES+1]; 
  int nc = 0;
  Point next_point;

  if (simple_search) {
    next_point = next_square_simple(board);
  }
  else {
    next_point = next_square_restricted(board);
  }

  possible_values(next_point, board, candidates, &nc);

  for (int i=0; i<nc; ++i) {
    make_move(next_point, board, candidates[i]);
    backtrack(board, calls, simple_search);
    if (is_complete(board)) {
      return;
    }

    unmake_move(next_point, board);
  }
}

void example_backtrack(void) {
  int calls = 0;

  Board* b = init_board(INPUT_FILE);
  printf("\n### without candidate prioritisation\n");
  print_board(b);

  backtrack(b, &calls, true);
  print_board(b);
  printf("total backtrack calls: %d\n", calls);

  b = init_board(INPUT_FILE);
  calls = 0;
  printf("\n### with candidate prioritisation\n");

  print_board(b);
  backtrack(b, &calls, false);
  print_board(b);
  printf("total backtrack calls: %d\n", calls);
}
