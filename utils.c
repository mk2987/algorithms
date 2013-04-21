#include <stdio.h>
#include <assert.h>
#include "utils.h"

void verifyArrayIsSorted(int array[], int length, SortDirection direction)
{
    int i = 0;

    assert(direction == ASCENDING || direction == DESCENDING);

    fprintf(stdout, "Verifying array is sorting in %s order...",
            direction == ASCENDING ? "ascending" : "descending");

    for (i = 0; i < length - 1; i++) {
        if (direction == ASCENDING) {
            assert(array[i] < array[i+1]);
        }
        else {
            assert(array[i] > array[i+1]);
        }
    }

    printf("OK\n");
}

void printArray(int array[], int length)
{
    int i;

    printf("array = {\n ");
    printf("\t");

    for (i = 0; i < length; i++) {
        printf(" %d,", array[i]);
        if ((i + 1) % 10 == 0 && i < length - 1) {
            printf("\n\t");
        }
    }

    printf("\n");
    printf("        }\n");
}
