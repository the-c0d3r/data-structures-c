#include "bubblesort.h"

/**
 * @brief implementation of bubblesort algorithm
 * @param array : the array to sort
 * @param n : the number of elements in array
 */
void bubblesort(int* array, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (array[i] < array[j]) {
                swap(&array[i], &array[j]);
            }
        }
    }
}

/**
 * @brief swap the given values for a and b
 * @param a : the first value to swap
 * @param b : the second value to swap
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
