#include <stdio.h>
#include <assert.h>
#include "utils.h"

void verifyArrayIsSorted(int array[], int length, SortDirection direction)
{
    int i = 0;

    assert(direction == ASCENDING || direction == DESCENDING);

    fprintf(stderr, "Verifying array is sorting in %s order...\n",
            direction == ASCENDING ? "ascending" : "descending");

    for (i = 0; i < length - 1; i++) {
        if (direction == ASCENDING) {
            if (array[i] > array[i+1]) {
                fprintf(stderr, "Verification failed at i = %d\n", i);
                fprintf(stderr, "FAILED!\n");
                return;
            }
        }
        else {
            if (array[i] < array[i+1]) {
                fprintf(stderr, "Verification failed at i = %d\n", i);
                fprintf(stderr, "FAILED!\n");
                return;
            }
        }
    }

    fprintf(stderr, "PASSED\n");
}

void swap(int *A, int *B)
{
    int temp;
    assert(A && B);

    temp = *A;
    *A = *B;
    *B = temp;
}

void printArray(int array[], int length, const char* name)
{
    int i;

    fprintf(stderr, "%s[] = { ", name);

    for (i = 0; i < length; i++) {
        fprintf(stderr, " %d,", array[i]);
    }

    fprintf(stderr, "}\n");
}
