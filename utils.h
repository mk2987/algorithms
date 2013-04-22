#ifndef __UTILS_H__
#define __UTILS_H__

typedef enum {
    ASCENDING,
    DESCENDING
} SortDirection;

void verifyArrayIsSorted(int array[], int length, SortDirection direction);
void printArray(int array[], int length, const char* name);
void swap(int *A, int *B);

#endif /* __UTILS_H__ */
