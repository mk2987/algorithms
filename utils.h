#ifndef __UTILS_H__
#define __UTILS_H__

typedef enum {
    ASCENDING,
    DESCENDING
} SortDirection;

void verifyArrayIsSorted(int array[], int length, SortDirection direction);
void printArray(int array[], int length);

#endif /* __UTILS_H__ */
