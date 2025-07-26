#include "sorting.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

char* array_init(char* string) {
  // gotta be done this way as string literals are stored in read only memory
  // trying to mutate string literals gives segmentation faults
  char* result = calloc(sizeof(char), strlen(string));
  strcpy(result, string);

  return result;
}

void swap(char* c1, char* c2) {
  char swap = *c1;
  *c1 = *c2;
  *c2 = swap;
}

void selection_sort(char* array) {
  char min_value;
  size_t min_index;

  for (size_t i = 0; i < strlen(array); ++i) {
    min_value = 127;

    for (size_t j = i; j < strlen(array); ++j) {
      if (array[j] < min_value) {
        min_value = array[j];
        min_index = j;
      }
    }

    array[min_index] = array[i];
    array[i] = min_value;
  }
}

void insertion_sort(char* array) {
  for (int index = 0; index < strlen(array); ++index) {
    for (int j = index; j > 0; --j) {
      if (array[j] < array[j - 1]) {
        swap(&array[j], &array[j - 1]);
      }
    }
  }
}

void merge(char* array, int low, int middle, int high) {
  Queue* sub1 = queue_init();
  Queue* sub2 = queue_init();
  char pop1;
  char pop2;

  for (int i = low; i < middle; ++i) {
    enqueue(sub1, array[i]);
  }

  for (int i = middle; i < high; ++i) {
    enqueue(sub2, array[i]);
  }

  pop1 = dequeue(sub1);
  pop2 = dequeue(sub2);

  for (int i = low; i < high; ++i) {
    if (pop1 == 0) {
      array[i] = pop2;
      pop2 = dequeue(sub2);
      continue;
    }

    if (pop2 == 0) {
      array[i] = pop1;
      pop1 = dequeue(sub1);
      continue;
    }

    if (pop1 < pop2) {
      array[i] = pop1;
      pop1 = dequeue(sub1);
    } else {
      array[i] = pop2;
      pop2 = dequeue(sub2);
    }
  }
}

void merge_sort(char* array, int low, int high) {
  int middle;

  if (high - low > 1) {
    middle = (low + high) / 2;
    merge_sort(array, low, middle);
    merge_sort(array, middle, high);

    merge(array, low, middle, high);
  }
}

Heap* heap_init(void) {
  Heap* new_heap = malloc(sizeof(Heap));

  new_heap->size = 0;
  return new_heap;
}

int index_parent(int index) {
  if (index == 0) {
    return -1;
  }

  return (int)index / 2;
}

int index_young_child(int index) { return index * 2; }

int index_old_child(int index) { return (index * 2) + 1; }

void heap_bubble_up(Heap* heap, int index) {
  if (index_parent(index) == -1) {
    return;
  }

  char child_val = heap->data[index];
  char par_val = heap->data[index_parent(index)];

  if (child_val < par_val) {
    heap->data[index] = par_val;
    heap->data[index_parent(index)] = child_val;

    heap_bubble_up(heap, index_parent(index));
  }
}

void heap_insert(Heap* heap, char value) {
  if (heap->size == HEAP_SIZE) {
    printf("HEAP OVERFLOW!!!\n");
    return;
  }

  heap->size++;
  heap->data[heap->size] = value;
  heap_bubble_up(heap, heap->size);
}

void heap_bubble_down(Heap* heap, int index) {
  int min_index = index;
  char value = heap->data[index];

  int young_index = index_young_child(index);
  int old_index = index_old_child(index);

  if (young_index <= heap->size) {
    if (heap->data[young_index] < value) {
      min_index = young_index;
      value = heap->data[young_index];
    }
  }

  if (old_index <= heap->size) {
    if (heap->data[old_index] < value) {
      min_index = old_index;
      value = heap->data[old_index];
    }
  }

  if (min_index != index) {
    heap->data[min_index] = heap->data[index];
    heap->data[index] = value;
    heap_bubble_down(heap, min_index);
  }
}

char heap_pop_min(Heap* heap) {
  if (heap->size <= 0) {
    printf("tried to pop from empty heap!\n");
    return -1;
  }

  char min = heap->data[1];
  heap->data[1] = heap->data[heap->size];
  heap->size--;
  heap_bubble_down(heap, 1);

  return min;
}

void heap_sort(char* array) {
  Heap* heap = heap_init();

  for (int i = 0; i < strlen(array); ++i) {
    heap_insert(heap, array[i]);
  }

  for (int i = 0; i < strlen(array); ++i) {
    array[i] = heap_pop_min(heap);
  }
}

void my_print(char* array, int low, int high) {
  for (int i = low; i <= high; ++i) {
    printf("%c", array[i]);
  }
}

static int partition(char* array, int low, int high) {
  int min_index = low;
  int p_index = low + (rand() % (high - low));

  // swap with last element
  swap(&array[p_index], &array[high]);
  p_index = high;

  for (int i = low; i < high; ++i) {
    if (array[i] < array[p_index]) {
      swap(&array[i], &array[min_index]);
      min_index++;
    }
  }

  swap(&array[high], &array[min_index]);

  return min_index;
}

void quick_sort(char* array, int low, int high) {
  if (high > low) {
    int p = partition(array, low, high);
    quick_sort(array, low, p - 1);
    quick_sort(array, p + 1, high);
  }
}

void example_sorting(void) {
  char* initial_string = "the five boxing wizards jump quickly";
  printf("## Sorting\n");
  printf("Initial String:\t\t'%s'\n", initial_string);
  printf("\n");

  char* selection_string = array_init("the five boxing wizards jump quickly");
  selection_sort(selection_string);
  printf("Selection Sort:\t\t'%s'\n", selection_string);

  char* insertion_string = array_init("the five boxing wizards jump quickly");
  insertion_sort(insertion_string);
  printf("Insertion Sort:\t\t'%s'\n", insertion_string);

  char* merge_string = array_init("the five boxing wizards jump quickly");
  merge_sort(merge_string, 0, strlen(merge_string));
  printf("MergeSort:\t\t'%s'\n", merge_string);

  char* heap_string = array_init("the five boxing wizards jump quickly");
  heap_sort(heap_string);
  printf("HeapSort:\t\t'%s'\n", heap_string);
  //
  char* quick_string = array_init("the five boxing wizards jump quickly");
  quick_sort(quick_string, 0, strlen(quick_string) - 1);
  printf("QuickSort:\t\t'%s'\n", quick_string);
}
