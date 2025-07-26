#include "backtrack.h"
#include "binary_tree.h"
#include "dictionary.h"
#include "dynamic.h"
#include "dynamic_array.h"
#include "graph.h"
#include "hashing.h"
#include "knapsack.h"
#include "linked_list.h"
#include "partition.h"
#include "priority_queue.h"
#include "queue.h"
#include "sorting.h"
#include "stack.h"
#include "weighted_graph.h"

int main(void) {
  printf(
      "\t1 -\tData Structures\n"
      "\t2 -\tSorting\n"
      "\t3 -\tHashing and Randomized Algorithms\n"
      "\t4 -\tGraphs\n"
      "\t5 -\tWeighted Graphs\n"
      "\t6 -\tCombinatorial Search\n"
      "\t7 -\tDynamic Programming\n"
      "\n"
      "Enter number: ");

  int input_val;
  scanf("%d", &input_val);
  printf("\n");

  switch (input_val) {
    case 1:
      example_dynarray();
      printf("\n\n");
      example_linked_list();
      printf("\n\n");
      example_stack();
      printf("\n\n");
      example_queue();
      printf("\n\n");
      example_dictionary();
      printf("\n\n");
      example_binary_tree();
      printf("\n\n");
      example_priority_queue();
      break;

    case 2:
      example_sorting();
      break;

    case 3:
      example_hashing();
      break;

    case 4:
      example_graph();
      break;

    case 5:
      example_weighted_graph();
      break;

    case 6:
      example_backtrack();
      break;

    case 7:
      example_dynamic();
      example_knapsack();
      example_partition();
      break;

    default:
      printf("invalid number entered, please enter 1-7\n");
      exit(EXIT_FAILURE);
  }

  return 0;
}
