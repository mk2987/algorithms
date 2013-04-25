#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

typedef struct BinaryTreeNode_st {
    int data;
    struct BinaryTreeNode_st *parent;
    struct BinaryTreeNode_st *leftChild;
    struct BinaryTreeNode_st *rightChild;
} *BinaryTreeNode;

// Takes O(n) time.
static void breadthFirstTraverse(BinaryTreeNode head, FILE *file, bool printNodeOnly)
{
    if (head == NULL) {
        return;
    }

    if (printNodeOnly) {
        fprintf(file, "node%d[label = \"<f0> |<f1>% d|<f2> \"];\n", head->data, head->data);
    }
    else {
        if (head->leftChild != NULL) {
            fprintf(file, "node%d:f0 -> node%d:f1;\n", head->data, head->leftChild->data);
        }

        if (head->rightChild != NULL) {
            fprintf(file, "node%d:f2 -> node%d:f1;\n", head->data, head->rightChild->data);
        }
    }

    // Now visit the child nodes
    breadthFirstTraverse(head->leftChild, file, printNodeOnly);
    breadthFirstTraverse(head->rightChild, file, printNodeOnly);
}

static void depthFirstTraverseInOrder(BinaryTreeNode head, FILE *file)
{
    if (head == NULL) {
        return;
    }

    depthFirstTraverseInOrder(head->leftChild, file);

    fprintf(file, "%d -> ", head->data);
    
    depthFirstTraverseInOrder(head->rightChild, file);
}

static void depthFirstTraversePreOrder(BinaryTreeNode head, FILE *file)
{
    if (head == NULL) {
        return;
    }

    fprintf(file, "%d -> ", head->data);
    
    depthFirstTraversePreOrder(head->leftChild, file);
    depthFirstTraversePreOrder(head->rightChild, file);
}

static void depthFirstTraversePostOrder(BinaryTreeNode head, FILE *file)
{
    if (head == NULL) {
        return;
    }

    depthFirstTraversePostOrder(head->leftChild, file);
    depthFirstTraversePostOrder(head->rightChild, file);
    fprintf(file, "%d -> ", head->data);
}

// Worst case time for binary tree insertion = O(n²),
// which happens when a sorted array is inserted in the
// binary tree. The first element takes 1 comparision, the
// second takes 2, the third takes 3 and so on.
// Common errors: The malloc must have a sizeof(*node) and
// not sizeof (*BinaryTreeNode)
static void binaryTreeInsert (BinaryTreeNode *head, int data)
{
    BinaryTreeNode node = malloc(sizeof(*node));
    // Track the current node being examined
    BinaryTreeNode curr = *head, prev = NULL;

    node->data = data;
    node->parent = NULL;
    node->leftChild = NULL;
    node->rightChild = NULL;

    // The tree was empty
    if (*head == NULL) {
        *head = node;
        return;
    }

    // Find the correct place for this node
    // This can also be while(1), since we'll
    // never land at curr = NULL
    while (curr != NULL) {
        if (curr->data > data) {
            // If we've found the right place,
            // insert the node here.
            if (curr->leftChild == NULL) {
                curr->leftChild = node;
                node->parent = curr;
                return;
            }

            // Keep going
            curr = curr->leftChild;
        }
        else if (curr->data < data) {
            // If we've found the right place,
            // insert the node here.
            if (curr->rightChild == NULL) {
                curr->rightChild = node;
                node->parent = curr;
                return;
            }

            // Keep going
            curr = curr->rightChild;
        }
        else {
            // An identical element is already present,
            // nothing more to do.
            free(node);
            return;
        }
    }
}

//          Average   Worst case
//  Space   O(n)      O(n)
//  Search  O(lg n)   O(n)
//  Insert  O(lg n)   O(n)
//  Delete  O(lg n)   O(n)
void binaryTree(int array[], int length, const char *fileName)
{
    int i;
    BinaryTreeNode head = NULL;
    FILE *file = fopen(fileName, "w");

    if (file == NULL) {
        fprintf(stderr, "Failed to open temp dot file\n");
        return;
    }

    for (i = 0; i < length; i++) {
        binaryTreeInsert(&head, array[i]);
    }

    fprintf(file, "digraph G {\n");
    fprintf(file, "node [shape = record, height = .1];\n");
    breadthFirstTraverse(head, file, true);
    breadthFirstTraverse(head, file, false);
    fprintf(file, "}\n");

    fclose(file);

    fprintf(stderr, "Depth first traversal: Pre Order\n");
    depthFirstTraversePreOrder(head, stderr);
    fprintf(stderr, "X\n");

    fprintf(stderr, "Depth first traversal: In Order\n");
    depthFirstTraverseInOrder(head, stderr);
    fprintf(stderr, "X\n");

    fprintf(stderr, "Depth first traversal: Post Order\n");
    depthFirstTraversePostOrder(head, stderr);
    fprintf(stderr, "X\n");
}

