#include<iostream>
#include<stack>
#include<list>
#include<cstdio>

using namespace std;

class Node {
public:
    Node (int value = 0): visited(false) {
        this->value = value;
    }

    int value;
    bool visited;
    list<Node*> adjList;
};

/* REMEMBER:
 * stack and list make COPIES of whatever value is stored in them.
 * 
 * METHOD:
 * Store each value */
void dfs_iterative (Node& head) {
    head.visited = true;
    stack<Node*> s;
    s.push(&head);
    fprintf(stderr, "%d -> ", head.value);

    while (s.size() != 0) {
        Node *t = s.top();
        list<Node*>::iterator it;

        for (it = t->adjList.begin(); it != t->adjList.end(); it++) {
            if (!(*it)->visited) {
                s.push(*it);
                (*it)->visited = true;
                fprintf(stderr, "%d -> ", (*it)->value);
                break;
            }
        }

        if (it == t->adjList.end()) {
            s.pop();
        }
    }
    fprintf(stderr, "X\n");
}

void dfs_recursive (Node& head) {
    if (head.visited)
        return;
    
    head.visited = true;
    fprintf(stderr, "%d -> ", head.value);

    list<Node*>::iterator it;
    for (it = head.adjList.begin(); it != head.adjList.end(); it++) {
        if (!(*it)->visited) {
            dfs_recursive(**it);
        }
    }
}

int main(void) {
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);
    Node n6(6);
    Node n7(7);
    Node n8(8);
    Node n9(9);
    Node n10(10);
    Node n11(11);
    Node n12(12);

    /* list.push_back creates a COPY of the element passed in */
    n1.adjList.push_back(&n2);
    n1.adjList.push_back(&n7);
    n1.adjList.push_back(&n8);

    n2.adjList.push_back(&n1);
    n2.adjList.push_back(&n3);
    n2.adjList.push_back(&n5);


    n3.adjList.push_back(&n2);
    n3.adjList.push_back(&n4);
    n3.adjList.push_back(&n6);

    n4.adjList.push_back(&n3);
    n4.adjList.push_back(&n5);

    n5.adjList.push_back(&n2);
    n5.adjList.push_back(&n4);

    n6.adjList.push_back(&n3);

    n7.adjList.push_back(&n1);

    n8.adjList.push_back(&n1);
    n8.adjList.push_back(&n9);
    n8.adjList.push_back(&n12);

    n9.adjList.push_back(&n8);
    n9.adjList.push_back(&n10);
    n9.adjList.push_back(&n11);

    n10.adjList.push_back(&n9);

    n11.adjList.push_back(&n9);

    n12.adjList.push_back(&n8);

    cout << "Calling iterative dfs " << endl;
    dfs_iterative(n1);

    n1.visited = false;
    n2.visited = false;
    n3.visited = false;
    n4.visited = false;
    n5.visited = false;
    n6.visited = false;
    n7.visited = false;
    n8.visited = false;
    n9.visited = false;
    n10.visited = false;
    n11.visited = false;
    n12.visited = false;

    cout << "Calling recursive dfs " << endl;
    dfs_recursive(n1);
    cout << "X" << endl;

    return 0;
}
