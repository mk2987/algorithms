#include <stdio.h>
#include "tree.h"
#include "utils.h"

// If an array corresponds to a heap,
// this is how to calculate parent and
// child indices.
// For an array, subtract 1 from the return value.
static int parent(int position)
{
    // floor(position/2)
    return position / 2;
}

// For an array, add 1 to the return value.
static int leftChild(int position)
{
    return 2 * position;
}

// For an array, add 1 to the return value.
static int rightChild(int position)
{
    return 2 * position + 1;
}

// heapSize represents how many elements in the heap are stored within
// array A. That is, although A[0..length-1] may contain numbers, only the
// elements A[0..heapSize-1], where 0 <= heapSize <= length, are valid
// elements of the heap.
// O(lg n) worst case time.
static void maxHeapify(int A[], int i, int heapSize)
{
    // Because the array A starts at 0.
    int left  = leftChild(i) + 1;
    int right = rightChild(i) + 1;
    int largest = i;

    // Find the largest element among the given element,
    // its left child and right child
    if (left < heapSize && A[left] > A[largest]) {
        largest = left;
    }

    if (right < heapSize && A[right] > A[largest]) {
        largest = right;
    }

    // If i is not the largest, we need to recurse further
    if (largest != i) {
        swap(&A[i], &A[largest]);

        // A[largest] now has the shifted data, which may
        // need to be shifted further.
        maxHeapify(A, largest, heapSize);
    }
}

void buildMaxHeap(int A[], int length)
{
    // The array A[] is the array representation of a heap.
    // A heap is a nearly complete binary tree. Therefore
    // the elements in the last array are located at
    // floor(length/2) + 1, floor(length/2) + 2 and so on.
    int i;
    int heapSize = length;

    // Loop invariant: At the beginning of every loop, the
    // left and right childrean are roots of max heaps.
    for (i = length/2; i >= 0; i--) {
        maxHeapify(A, i, heapSize);
    }
}
