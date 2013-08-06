#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "utils.h"
#include "heap.h"

// Sorts in place, stable.
// Best time is O(n) when array is already sorted
// and no swaps occur. Worst case is when the array
// is reverse sorted, number of swaps are n(n+1)/2 = O(n²)
// Average case = O(n²). Space complexity = O(1);
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
// Best time O(n²) = worst case = Average case.
// Common errors:
// - In the second for loop, if A[j] < min, set
//   min = A[j] and not A[i]
void selectionSort(int A[], int length)
{
    int i, j;
    int min, loc;

    for (i = 0; i < length; i++) {
        // During every iteration of the outer loop, the
        // portion of the array to the left of element i
        // are already sorted.
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

// Sorts in place, stable.
// Called insertion sort because the element i being checked
// in inseted in its proper place in the array A[0..i-1].
// The array portion to the left of the current element is
// always sorted.
// Best case = O(n) comparisons, O(1) swaps
// Worst case = O(n²) swaps when the array is reverse sorted.
// Average case = O(n²).
// Common errors:
// - In the while loop, while comparing elements, we need to
//   keep shifting forward till we find an element that's <=
//   A[i], and not j+1;
void insertionSort(int A[], int length)
{
    int i, j;
    int elt;

    for (i = 0; i < length; i++) {
        // The current element we're trying to sort
        elt = A[i];

        // The array to the left of the current element is
        // always sorted. To fit the current element, shift
        // the elements forward to create a hole.
        j = i - 1;
        while (j >= 0 && A[j] > elt) {
            A[j+1] = A[j];
            j--;
        }

        // Put the element in the hole.
        A[j+1] = elt;
    }
}

// Sorts in place, stable
// Called heap sort because we first make a heap from the array
// Worst case = O(nlogn)
// Best case = Ω(n), O(nlogn)
// Average case = O(nlogn)
void heapSort(int A[], int length)
{
    int i;
    int heapSize = length;

    buildMaxHeap(A, length);

    for (i = 0; i < length; i++) {
        // The largest element has been moved to the end of
        // the array, and the last element to the front.
        swap(&A[0], &A[heapSize - 1]);
        heapSize--;

        // The new element may need to be adjusted
        maxHeapify(A, 0, heapSize);
    }
}

// Quicksort partitioning
// Worst case: O(n) comparisions, O(n) swaps
// when the array is already sorted, for in that case
// each comparision will result in a swap with itself.
static int partition(int A[], int p, int r)
{
    // x is the pivot element
    int x = A[r];
    int i = p - 1;
    int j;

    // Divide A[p..r] into two partitions, the first
    // part has elements < x and the second has elements
    // > x.
    // First part A[p..i]
    // Second part A[i+1..r]
    for (j = p; j <= (r-1); j++) {
        if (A[j] < x) {
            i = i + 1;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i+1], &A[r]);
    return i+1;
}

// Sorts in place, stable
// Worst case time O(n²)
// Average case time O(nlogn)
// Best case time O(nlogn)
void quickSort(int A[], int p, int r)
{
    // q is the pivot
    int q;

    if (p < r) {
        q = partition(A, p, r);
        quickSort(A, p, q-1);
        quickSort(A, q, r);
    }
}

// Takes O(n) extra space in B[]
// For a version that does not take any extra space, store
// the elements of the merged array in A[] itself, and the
// displaced elements of A[] in the space vacated in B[].
// The merge function assumes that the arrays A[p..q] and
// A[q+1..r] are both sorted.
static void merge(int A[], int B[], int p, int q, int r)
{
    int left = p;
    int right = q + 1;
    int i;

    // This for loop alongwith the two while loops
    // takes a total of O(n) time
    // B[] is scratch space
    for (i = p; (left <= q && right <= r); i++) {

        // Figure out which element goes into B[] first
        if (A[left] < A[right])
            B[i] = A[left++];
        else
            B[i] = A[right++];
    }

    // Only one of these while loops will run
    while(left <= q)
        B[i++] = A[left++];

    while(right <= r)
        B[i++] = A[right++];

    // This takes O(n) time again
    for (i = p; i <= r; i++)
        A[i] = B[i];
}

// Does NOT sort in place, stable
// Takes O(n) additional space
// Worst case time O(nlogn)
// Best case time O(nlogn)
// B[] is scratch space, as wide as A[]
void mergeSort(int A[], int B[], int p, int r)
{
    // There need to be at least two elements
    // left to require sorting.
    if (p < r) {

        // floor(p+r)/2
        int q = (p + r)/2;

        mergeSort(A, B, p, q);
        mergeSort(A, B, q+1, r);

        merge(A, B, p, q, r);
    }
}

