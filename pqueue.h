#ifndef __PQUEUE_H__
#define __PQUEUE_H__

int heapMaximum(int A[]);
int heapExtractMax(int A[], int *heapSize);
void maxHeapInsert(int **A, int key, int *heapSize);

#endif
