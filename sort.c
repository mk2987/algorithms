#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "utils.h"

// Sorts in place, stable.
// Best time is O(n) when array is already sorted
// and no swaps occur. Worst case is when the array
// is reverse sorted, number of swaps are n(n+1)/2
// Common errors:
// - The number of sorted elements at the end of the array
//   only grows AFTER the for loop is done.
// - The "swapped" boolean must be initialized to false at
//   the beginning of the for loop.
void bubbleSort(int A[], int length)
{
    bool swapped;
    int i, sorted_elements = 0;;

    // Keep looping while there are swaps
    do {
        swapped = false;

        for (i = 0; i < length - 1 - sorted_elements; i++) {
           if (A[i] > A[i + 1]) {
               swap(&A[i], &A[i + 1]);
               swapped = true;
           }
        }

        // Optimization: At the end of the for loop, one more
        // element at the end of the array is sorted.
        sorted_elements++;

    } while(swapped);
}

// Sorts in place, stable.
// Called selection sort because on each iteration of
// the outer loop, the minimum element is chosen.
// Best time O(n²)
// Common errors:
// - In the second for loop, if A[j] < min, set
//   min = A[j] and not A[i] 
void selectionSort(int A[], int length)
{
    int i, j;
    int min, loc;

    for (i = 0; i < length; i++) {
        // In every iteration of the outer loop, the
        // first i elements are considered to be sorted.
        min = A[i];
        loc = i;

        // Find the MIN from the remaining elements.
        for (j = i+1; j < length; j++) {
            if (A[j] < min) {
                min = A[j];
                loc = j;
            }
        }

        swap(&A[i], &A[loc]);
    }
}

void insertionSort(int A[], int length)
{
}
