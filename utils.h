#ifndef __UTILS_H__
#define __UTILS_H__

typedef enum {
    ASCENDING,
    DESCENDING
} SortDirection;

typedef struct BinaryTreeNode_st {
    int data;
    struct BinaryTreeNode_st *parent;
    struct BinaryTreeNode_st *leftChild;
    struct BinaryTreeNode_st *rightChild;
} *BinaryTreeNode;

void verifyArrayIsSorted(int array[], int length, SortDirection direction);
void printArray(int array[], int length, const char* name);
void swap(int *A, int *B);
void printTree(BinaryTreeNode head, FILE *file);
void printFlattenedTree(int A[], int maxLength, FILE *file);

#endif /* __UTILS_H__ */
