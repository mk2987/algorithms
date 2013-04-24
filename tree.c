#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void breadthFirstTraverse(BinaryTreeNode head, FILE *file)
{
    if (head == NULL) {
        return;
    }

    if (head->leftChild != NULL)
        fprintf(file, "%d:sw -> %d:n;\n", head->data, head->leftChild->data);

    if (head->rightChild != NULL)
        fprintf(file, "%d:se -> %d:n;\n", head->data, head->rightChild->data);

    // Now visit the child nodes
    breadthFirstTraverse(head->leftChild, file);
    breadthFirstTraverse(head->rightChild, file);
}

void binaryTreeInsert (BinaryTreeNode *head, int data)
{
    BinaryTreeNode node = malloc(sizeof(BinaryTreeNode));
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
void binaryTree(int array[], int length)
{
    int i;
    BinaryTreeNode head = NULL;
    FILE *file = fopen("/tmp/binarytree.dot", "w");

    if (file == NULL) {
        fprintf(stderr, "Failed to open temp dot file\n");
        return;
    }

    for (i = 0; i < length; i++) {
        binaryTreeInsert(&head, array[i]);
    }

    fprintf(file, "digraph G {\n");
    breadthFirstTraverse(head, file);
    fprintf(file, "}\n");

    fclose(file);
}

