#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"

/*
 * Dynamic Array
 *
 * dynarray_print   - helper function (unused array elements are represented with '_')
 * dynarray_append  - O(1) with occasional O(n) when array needs to be extended
 *                  - can be considered O(1) as the average element will only be copied twice
 * dynarray_init    - O(1)
 * dynarray_pop     - O(n) due to shuffling of elements
*/


void dynarray_print(Dynarray* array) {
    printf("[");

    for (size_t i=0; i< array->length; ++i) {
        if (array->data[i] == 0) {
            printf("_");
        }
        else {
            printf("%c", array->data[i]);
        }

        if (i < array->length-1) {
            printf(", ");
        }
    }

    printf("]\n");
}


void dynarray_append(Dynarray* array, char new) {
    if (array->length == array->data_end) {
        char* new_array = calloc(array->length * 2, sizeof(char));

        for (size_t i=0; i < array->data_end; ++i) {
            new_array[i] = array->data[i];
        }

        free(array->data);

        array->data = new_array;
        array->length *= 2;
    }

    array->data[array->data_end] = new;
    array->data_end++;
}


Dynarray* dynarray_init(size_t len) {
    Dynarray* new_array = malloc(sizeof(Dynarray));

    new_array->length = len;
    new_array->data_end = 0;
    new_array->data = calloc(len, sizeof(char));

    return new_array;
}


char dynarray_pop(Dynarray* array, size_t index) {
    if (index >= array->data_end) {
        printf("tried to pop with index outside array bounds\n");
        return -1;
    }

    char result = array->data[index];

    // shuffle remaining elements forward to fill gap
    for (size_t i=index; i<array->data_end ; ++i) {
        if (i == array->data_end-1) {
            array->data[i] = 0;
        }
        else {
            array->data[i] = array->data[i+1];
        }
    }
    array->data_end--;

    return result;
}


void example_dynarray(void) {
    Dynarray* example_array = dynarray_init(2);
    char* string = "dynamic array";

    printf("## Dynamic Array example\n");
    printf("##\n");
    printf("## appending to array\n");
    printf("##\n");

    for (int i=0; i<strlen(string); ++i) {
        dynarray_append(example_array, string[i]);
        dynarray_print(example_array);
    }

    printf("##\n");
    printf("## popping from array\n");
    printf("##\n");
    dynarray_print(example_array);

    for (int i=0; i<8; ++i) {
        dynarray_pop(example_array, 0);
        dynarray_print(example_array);
    }
}


int main(void) {
    example_dynarray();
}
