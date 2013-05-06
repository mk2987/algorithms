#include <stdio.h>
#include <string.h>
#include "main.h"
#include "utils.h"
#include "sort.h"
#include "tree.h"
#include "heap.h"

extern int UNSORTED_ARRAY[];

static void prepare(int array[], int length)
{
    memcpy(array, UNSORTED_ARRAY, NUM_ELTS * sizeof (int));
    printArray(array, NUM_ELTS, "before");
}

static void check(int array[], int length)
{
    printArray(array, NUM_ELTS, "after");
    verifyArrayIsSorted(array, NUM_ELTS, ASCENDING);
}

int main ()
{
    int sortedArray[NUM_ELTS];

    fprintf(stderr, "====== STARTING ======\n");

    fprintf(stderr, "Running Bubble Sort\n");
    prepare(sortedArray, NUM_ELTS);
    bubbleSort(sortedArray, NUM_ELTS);
    check(sortedArray, NUM_ELTS);

    fprintf(stderr, "Running Selection Sort\n");
    prepare(sortedArray, NUM_ELTS);
    selectionSort(sortedArray, NUM_ELTS);
    check(sortedArray, NUM_ELTS);

    fprintf(stderr, "Running Insertion Sort\n");
    prepare(sortedArray, NUM_ELTS);
    insertionSort(sortedArray, NUM_ELTS);
    check(sortedArray, NUM_ELTS);

    fprintf(stderr, "Running Heap Sort\n");
    prepare(sortedArray, NUM_ELTS);
    heapSort(sortedArray, NUM_ELTS);
    check(sortedArray, NUM_ELTS);

    fprintf(stderr, "Creating Binary Search Tree\n");
    prepare(sortedArray, NUM_ELTS);
    binaryTree(sortedArray, NUM_ELTS, stderr);

    fprintf(stderr, "Creating Max Heap\n");
    prepare(sortedArray, NUM_ELTS);
    buildMaxHeap(sortedArray, NUM_ELTS);
    printFlattenedTree(sortedArray, NUM_ELTS, stderr);

    fprintf(stderr, "====== EXITING ======\n");

    return 0;
}
