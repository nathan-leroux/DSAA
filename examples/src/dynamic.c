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

void diff_goal_cell(char* pattern, char* string, int* i, int* j) {
  *i = strlen(string) - 1;
  *j = strlen(pattern) - 1;
}

void print_matrix(Cell matrix[MAXSTRING+1][MAXSTRING+1], char* pattern, char* string) {
  printf("  ");
  for (int x=0; x<strlen(string); ++x) {
    printf("%c ", string[x]);
  }
  printf("\n");
  for (int y=0; y<strlen(pattern); ++y) {
    printf("%c ", pattern[y]);
    
    for (int x=0; x<strlen(string); ++x) {
      printf("%d ", matrix[x][y].value);
    }
    printf("\n");
  }
  printf("\n");
}

void backtrack_r(Cell matrix[MAXSTRING+1][MAXSTRING+1], int x, int y, char* s) {
  char next_char = 0;

  if (x <= 0 && y <= 0) {
    return;
  }

  if (matrix[x][y].parent == MATCH) {
    if (matrix[x][y].value == matrix[x-1][y-1].value) {
      next_char = 'M';
    }
    else {
      next_char = 'S';
    }
    --x;
    --y;
  }
  else if (matrix[x][y].parent == INSERT) {
    next_char = 'I';
    --y;
  }
  else if (matrix[x][y].parent == DELETE) {
    next_char = 'D';
    --x;
  }
  else {
    printf("parent value %d not valid!\n", matrix[x][y].parent);
    exit(EXIT_FAILURE);
  }

  *s = next_char;
  ++s;
  backtrack_r(matrix, x, y, s);
}


char* diff_retrace_steps(Cell (*matrix)[MAXSTRING+1], int* x, int* y) {
  int longest_len = *x+1;
  if (*y+1 > longest_len) {
    longest_len = *y+1;
  }

  char* new_buffer = malloc(sizeof(char)*(longest_len+1));
  char* reversed = malloc(sizeof(char)*(longest_len+1));
  new_buffer[longest_len] = '\0';
  reversed[longest_len] = '\0';

  // reverse the string
  backtrack_r(matrix, *x, *y, new_buffer);

  int last_index = strlen(new_buffer)-1;
  for (int i=0; i<=strlen(new_buffer); ++i) {
    reversed[last_index-i] = new_buffer[i];
  }
  
  return reversed;
}

// pattern is y axis, target (string) is x axis
void populate_matrix(Cell (*matrix)[MAXSTRING+1], char* pattern, char* string) {
  if (strlen(pattern) > MAXSTRING || strlen(string) > MAXSTRING) {
    printf("max string exceeded! exiting...\n");
    exit(EXIT_FAILURE);
  }

  int opt[3];

  // fill in base cases
  for (int i=0; i<=MAXSTRING; ++i) {
    matrix[0][i] = (Cell){i, INSERT};
    matrix[i][0] = (Cell){i, DELETE};
  }

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
          matrix[x][y].value = opt[i];
          matrix[x][y].parent = i;
        }
      }
    }
  }
}

void example_dynamic(void) {
  char* pattern = " chess";
  char* string = " checkers";
  int x, y;

  Cell matrix[MAXSTRING+1][MAXSTRING+1];

  populate_matrix(matrix, pattern, string);
  print_matrix(matrix, pattern, string);

  diff_goal_cell(pattern, string, &x, &y);
  printf("goal cell: %d,%d\n", x, y);

  char* steps = diff_retrace_steps(matrix, &x, &y);
  printf("order: %s\n", steps);
}
