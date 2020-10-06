#include <iostream>
using namespace std;

template <typename T> struct node {
    T data;
    int height;
    int balanceFactor;
    node *left = NULL;
    node *right = NULL;
};

template <typename T> class myAVLTree {
    struct node *root;

  public:
    myAVLTree() { root = NULL; }

    void insert(struct node *nodePtr) {
        if (root == NULL) {
            root = nodePtr;
        } else {
            if (nodePtr->data)
        }
    }
};

int main() { return 0; }