#include<iostream>
#include<queue>
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

void bfs(Node &head) {
    queue<Node*> q;
    q.push(&head);
    head.visited = true;

    while(q.size() != 0) {
        Node *t = q.front();
        q.pop();
        fprintf(stderr, "%d -> ", t->value);

        list<Node*>::iterator it;
        for (it = t->adjList.begin(); it != t->adjList.end(); it++) {
            if (!(*it)->visited) {
                (*it)->visited = true;
                q.push(*it);
            }
        }
    }
    
    fprintf(stderr, "X\n");
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
    n1.adjList.push_back(&n3);
    n1.adjList.push_back(&n4);

    n2.adjList.push_back(&n1);
    n2.adjList.push_back(&n5);
    n2.adjList.push_back(&n6);

    n3.adjList.push_back(&n1);

    n4.adjList.push_back(&n1);
    n4.adjList.push_back(&n7);
    n4.adjList.push_back(&n8);

    n5.adjList.push_back(&n2);
    n5.adjList.push_back(&n9);
    n5.adjList.push_back(&n10);

    n6.adjList.push_back(&n2);

    n7.adjList.push_back(&n4);
    n7.adjList.push_back(&n11);
    n7.adjList.push_back(&n12);

    n8.adjList.push_back(&n4);

    n9.adjList.push_back(&n5);

    n10.adjList.push_back(&n5);

    n11.adjList.push_back(&n7);

    n12.adjList.push_back(&n7);

    cout << "Calling bfs " << endl;
    bfs(n1);

    return 0;
}
