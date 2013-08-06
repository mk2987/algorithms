//
//  RED-BLACK TREE
//  
//  Properties:
//  1) Every node is either red or black.
//  2) The root is black
//  3) Every leaf (NIL) is black
//  4) If a node is red, then both its children are black
//  5) For each node, all paths from the node to descendant
//     leaves contain the same number of black nodes.
//
//  Black height of a node x
//  - The number of black nodes on any path from, but not
//    including the node x, down to a leaf.
//
//  The maximum height of a rb-tree with n internal nodes is 2lg(n+1).
//
//  Insertion and deletion take O(lg(n)) time
//
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdarg>

using namespace std;

bool debug = true;

void dbg(const char* format, ...) {
    if (debug) {
        char buffer[256];
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        printf(buffer);
        va_end(args);
    }
}

typedef enum {
    RED   = 0,
    BLACK = 1,
} Color;

template<typename T>
class Node {
    Node<T>* p;     // Parent
    Node<T>* l;     // Left child
    Node<T>* r;     // Right child
    Node<T>* NIL;   // Sentinel
    Color color;    // color
    T key;          // Payload

    void left_rotate (Node<T> **root, Node<T> *x);
    void right_rotate(Node<T> **root, Node<T> *y);

    void rb_insert_fixup(Node<T> **root, Node<T> *z);

public:
    Node<T>(Node<T> *p = NULL, Node<T> *l = NULL, Node<T> *r = NULL, T key = T()) {
        color = RED;
        NIL = NULL;
        dbg("New Node: p: %p, l: %p, r: %p, key: %s\n", p, l, r, key.print());
    }

    void rb_insert(Node<T> **root, Node<T> *z);
};

// O(1) time
template<typename T>
void Node<T>::left_rotate(Node<T> **root, Node<T> *x)
{
    Node<T> *y = x->r;

    if (y == NIL) {
        dbg("ERROR: left_rotate failed, x->r is NIL!\n");
        return;
    }

    // y's old left is now x's left
    // also adjust x->r's parent
    x->r = y->l;
    x->r->p = x;

    // x's old parent is now y's parent
    y->p = x->p;

    if (x->p == NIL) {
        // x was the root
        // make y the new root
        *root = y;
        dbg("New Root: p: %p, l: %p, r: %p, key: %s\n",
            y->p, y->l, y->r, y->key.print());
    }
    else if (x->p->l == x) {
        // x was its parent's left child
        // make y the parent's left child
        x->p->l = y;
    }
    else {
        // x was its parent's right child
        // make y the parent's right child
        x->p->r = y;
    }

    // y's new left is x
    y->l = x;

    // y becomes x's new parent
    x->p = y;
}

// O(1) time
template<typename T>
void Node<T>::right_rotate(Node<T> **root, Node<T> *y)
{
    Node<T> *x = y->l; 

    if (x == NIL) {
        dbg("ERROR: right_rotate failed, y->l is NIL!\n");
        return;
    }

    // x's old right is now y's left
    // also adjust y->l's parent
    y->l = x->r;
    y->l->p = y;

    if (y->p == NIL) {
        // y was the root
        // make x the new root
        *root = x;
        dbg("New Root: p: %p, l: %p, r: %p, key: %s\n",
            x->p, x->l, x->r, x->key.print());
    }
    else if (y->p->l == y) {
        // y was its parent's left child
        // make x the parent's left child
        y->p->l = x;
    }
    else {
        // y was its parent's right child
        // make x the parent's right child
        y->p->r = x;
    }

    // x's new right is y
    x->r = y;

    // x becomes y's new parent
    y->p = x;
}

template<typename T>
void Node<T>::rb_insert_fixup(Node<T> **root, Node<T> *z)
{
    // y is z's uncle
    Node<T> *y;

    // If z is the root, z-p = NIL which is black in color
    while(z->p->color == RED) {
        if (z->p = z->p->p->l) {
            // z's parent is the left child of z's grandfather

            // y is z's uncle
            y = z->p->p->r;

            if (y->color == RED) {
                // CASE 1
                // z's uncle is RED

                // make both siblings (y and z's parent RED)
                y->color = BLACK;
                z->p->color = BLACK;

                // make z's grandparent RED
                z->p->p->color = RED;

                // z moves up by 2
                z = z->p->p;
            }
            else {
                // z's uncle is BLACK 

                if (z = z->p->r) {
                    // CASE 2
                    // z is the right child of its parent

                    z = z->p;
                    left_rotate(root, z);
                }

                // CASE 3
                // z is the left child of its parent

                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(root, z->p->p);
            }
        }
        else {
            // z's parent is the right child of z's grandfather

            // y is z's uncle
            y = z->p->p->l;

            if (y->color == RED) {
                // CASE 1
                // z's uncle is RED

                // make both siblings (y and z's parent RED)
                y->color = BLACK;
                z->p->color = BLACK;

                // make z's grandparent RED
                z->p->p->color = RED;

                // z moves up by 2
                z = z->p->p;
            }
            else {
                // z's uncle is BLACK 
            }
        }
    }

    (*root)->color = BLACK;
}

template<typename T>
void Node<T>::rb_insert(Node<T> **root, Node<T> *z)
{
    // y points to the parent of x
    Node<T> *y = NIL;
    Node<T> *x = *root;

    // find the place where x belongs
    while (x != NIL) {
        y = x;

        if (x->key > z->key) {
            x = x->l;
        }
        else if (x->key < z->key) {
            x = x->r;
        }
        else {
            dbg("ERROR: ignoring attempt to insert duplicate element!\n");
            return;
        }
    }

    // y points to z's parent since it was one step behind x
    z->p = y;
    z->l = z->r = NIL;
    z->color = RED;

    rb_insert_fixup(root, z);
}

int main(void)
{
    return 0;
}
