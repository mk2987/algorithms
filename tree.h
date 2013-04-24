#ifndef __TREE_H__
#define __TREE_H__
typedef struct BinaryTreeNode_st {
    int data;
    struct BinaryTreeNode_st *parent;
    struct BinaryTreeNode_st *leftChild;
    struct BinaryTreeNode_st *rightChild;
} *BinaryTreeNode;

void binaryTreeInsert (BinaryTreeNode *head, int data);
void binaryTree(int array[], int length);
void breadthFirstTraverse(BinaryTreeNode head, FILE *file);
#endif // __TREE_H__
