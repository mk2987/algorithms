#include <stdio.h>
#include <stdlib.h>
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

    if (A == B)
        return;

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

// The head of the tree has the maximum height
static void findTreeHeight(BinaryTreeNode node, int currentHeight, int *maxHeight)
{
    if (!node)
        return;

    if (*maxHeight < currentHeight)
        *maxHeight = currentHeight;

    findTreeHeight(node->leftChild, currentHeight + 1, maxHeight);
    findTreeHeight(node->rightChild, currentHeight + 1, maxHeight);
}

// The head of the tree has the maximum height
static int treeHeight(BinaryTreeNode head)
{
    int maxHeight = 0;
    int currentHeight = 0;

    findTreeHeight(head, currentHeight, &maxHeight);

    return maxHeight;
}

// Must not print any newlines
// The head of the tree has the maximum height
static void printTreeNode(int data, int height, FILE *file)
{
    int numSpaces = (1 << height) - 1;
    int i;

#define SENTINEL (-1)
#define NUM_DIGITS 2
    numSpaces *= NUM_DIGITS;

    // Extra spaces in the beginning
    for (i = 0; i < NUM_DIGITS; i++) {
        fprintf(file, " ");
    }

    // Initial spaces
    for (i = 0; i < numSpaces; i++) {
        fprintf(file, " ");
    }

    // Element value
    if (data == SENTINEL) {
        for (i = 0; i < NUM_DIGITS; i++) {
            fprintf(file, " ");
        }
    }
    else
        fprintf(file, "%02d", data);

    // Following spaces
    for (i = 0; i < numSpaces; i++) {
        fprintf(file, " ");
    }
}

// Given any binary tree (may not be complete), this flattens the tree into
// the given array. The array should be initialized with a sentinel value. 
static void flattenTreeIntoArray(BinaryTreeNode node, int A[], int i, int maxLength)
{
    // Because the array starts at index 0
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (!node || i >= maxLength)
        return;

    A[i] = node->data;

    flattenTreeIntoArray(node->leftChild, A, left, maxLength);
    flattenTreeIntoArray(node->rightChild, A, right, maxLength);
}

void printFlattenedTree(int A[], int maxLength, FILE *file)
{
    int i;
    int currentLevel;
    int nextLevelStartIndex;
    int height;

    // Calculate the height of the tree this way to avoid
    // relying on (log maxLength)
    for (currentLevel = 0, i = 0; i < maxLength; i++) {
        nextLevelStartIndex = (1 << (currentLevel + 1)) - 1;
        if ((i + 1) == nextLevelStartIndex) {
            currentLevel++;
        }
    }

    height = currentLevel;

    for (currentLevel = 0, i = 0; i < maxLength; i++) {
        nextLevelStartIndex = (1 << (currentLevel + 1)) - 1;

        printTreeNode(A[i], height - currentLevel, file);

        if ((i + 1) == nextLevelStartIndex) {
            currentLevel++;
            fprintf(file, "\n\n");
        }
    }
    
    fprintf(file, "\n\n");
}

void printTree(BinaryTreeNode head, FILE *file)
{
    int i;

    int height = treeHeight(head);
    // Max elements in the tree had this been a fully complete tree
    int maxLength = (1 << (height + 1)) - 1;
    int *A;

    A = malloc(sizeof(int) * maxLength);

    // Initialize with a sentinel value
    for (i = 0; i < maxLength; i++) {
        A[i] = SENTINEL;
    }

    flattenTreeIntoArray(head, A, 0, maxLength);

    printFlattenedTree(A, maxLength, file);

    free(A);
}

