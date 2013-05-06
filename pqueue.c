#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "utils.h"

// A must hold a max heap
int heapMaximum(int A[])
{
    return A[0];
}

// If an array corresponds to a heap,
// this is how to calculate parent and
// child indices.
static int parent(int position)
{
    // floor(position/2)
    return ((position + 1)/2) - 1;
}

// Takes O(log n) time
int heapExtractMax(int A[], int *heapSize)
{
    int max;

    if (*heapSize <= 0) {
        fprintf(stderr, "Heap underflow!\n");
        return -1;
    }

    max = A[0];

    A[0] = A[*heapSize - 1];

    // Since an element has been removed
    (*heapSize)--;

    maxHeapify(A, 0, *heapSize);

    return max;
}

// Common error: The while loop must terminate when i <= 0,
// otherwise we'll end up dereferencing an invalid A index.
static void heapIncreaseKey(int A[], int i, int key)
{
    int parentIdx;
    int heapSize = i+1;

    if (key < A[i]) {
        fprintf(stderr, "new key is smaller than current key!\n");
        return;
    }

    A[i] = key;

    // Since the key has increased, and since the parent is bigger
    // than the previous key value, we can fix the max heap by just
    // comparing the new key with the parent.
    parentIdx = parent(i);
    while (i > 0 && A[i] > A[parentIdx]) {
        swap(&A[i], &A[parentIdx]);
        i = parentIdx;
        parentIdx = parent(i);
    }
}

// O(log n) worst case time
void maxHeapInsert(int **A, int key, int *heapSize)
{
    (*heapSize)++;
    *A = realloc(*A, sizeof(int) * (*heapSize));

    (*A)[*heapSize - 1] = -1;

    heapIncreaseKey(*A, *heapSize - 1, key);
}

