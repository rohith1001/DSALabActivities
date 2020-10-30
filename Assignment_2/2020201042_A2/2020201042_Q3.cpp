#include <bits/stdc++.h>
#include <iostream>
using namespace std;

template <typename T1, typename T2> class node {
  public:
    T1 data;
    T2 value;
    int height;
    int balanceFactor;
    node *left;
    node *right;

    node(T1 x, T2 y) {
        data = x;
        value = y;
        height = 0;
        balanceFactor = 0;
        left = NULL;
        right = NULL;
    }
};

template <class T> struct lesser {
    // my custom comparator
    // this will be our default comparator to build our BST
    bool operator()(const T &l, const T &r) { return l < r; }
};

template <typename T1, typename T2, typename Comparator = lesser<T1>> class myAVLTree {
    node<T1, T2> *gRoot = NULL;
    int nodeCount = 0;
    Comparator cmp;

  private:
    void update(node<T1, T2> *nodePtr) {
        int leftSubTreeHeight = (nodePtr->left == NULL) ? -1 : nodePtr->left->height;
        int rightSubTreeHeight = (nodePtr->right == NULL) ? -1 : nodePtr->right->height;

        nodePtr->height = max(leftSubTreeHeight, rightSubTreeHeight) + 1;
        nodePtr->balanceFactor = leftSubTreeHeight - rightSubTreeHeight;
    }

    node<T1, T2> *balance(node<T1, T2> *nodePtr) {
        if (nodePtr->balanceFactor == 2) {
            // left heavy subtree
            if (nodePtr->left->balanceFactor >= 0) {
                return leftLeftCase(nodePtr);
            } else {
                return leftRightCase(nodePtr);
            }
        } else if (nodePtr->balanceFactor == -2) {
            // right heavy subtree
            if (nodePtr->right->balanceFactor <= 0) {
                return rightRightCase(nodePtr);
            } else {
                return rightLeftCase(nodePtr);
            }
        }
        // no balancing required
        return nodePtr;
    }

    node<T1, T2> *leftLeftCase(node<T1, T2> *nodePtr) { return rightRotation(nodePtr); }

    node<T1, T2> *leftRightCase(node<T1, T2> *nodePtr) {
        nodePtr->left = leftRotation(nodePtr->left);
        return leftLeftCase(nodePtr);
    }

    node<T1, T2> *rightLeftCase(node<T1, T2> *nodePtr) {
        nodePtr->right = rightRotation(nodePtr->right);
        return rightRightCase(nodePtr);
    }

    node<T1, T2> *rightRightCase(node<T1, T2> *nodePtr) { return leftRotation(nodePtr); }

    node<T1, T2> *leftRotation(node<T1, T2> *nodePtr) {
        node<T1, T2> *newParent = nodePtr->right;
        nodePtr->right = newParent->left;
        newParent->left = nodePtr;
        update(nodePtr);
        update(newParent);
        return newParent;
    }

    node<T1, T2> *rightRotation(node<T1, T2> *nodePtr) {
        node<T1, T2> *newParent = nodePtr->left;
        nodePtr->left = newParent->right;
        newParent->right = nodePtr;
        update(nodePtr);
        update(newParent);
        return newParent;
    }

    node<T1, T2> *recursiveInsert(node<T1, T2> *root, node<T1, T2> *myNode) {
        if (root == NULL) {
            root = myNode;
            return root;
        }
        // if root is not NULL
        if (cmp(root->data, myNode->data)) {
            // this means root->data is less than myNode->data
            // or in other words, myNode->data is greater than root->data
            // of course go to the right subtree
            root->right = recursiveInsert(root->right, myNode);
        } else if (cmp(myNode->data, root->data)) {
            // this means root->data is greater than or equal to myNode->data
            // or in other words myNode->data <= root->data
            // so simply add it to the left subtree
            root->left = recursiveInsert(root->left, myNode);
        } else {
            cout << "Duplicates not allowed..." << endl;
            nodeCount--;
        }
        // for updating the balanceFactor and height of the node
        update(root);

        // balance the tree if it is unbalanced
        return balance(root);
    }

    node<T1, T2> *recursiveSearch(node<T1, T2> *root, T1 x) {
        if (root == NULL) {
            // key not found case
            return root;
        }
        if (cmp(root->data, x)) {
            // that means root->data is lesser than x
            // or x is greater than root->data
            // search in the right subtree
            return recursiveSearch(root->right, x);
        } else if (cmp(x, root->data)) {
            // that means x is lesser than root->data
            // search in the left subtree
            return recursiveSearch(root->left, x);
        }
        // this is success case
        // root->data = x
        return root;
    }

    void printInorder(node<T1, T2> *root) {
        if (root != NULL) {
            printInorder(root->left);
            cout << root->data << " ";
            printInorder(root->right);
        }
    }
    void printPreorder(node<T1, T2> *root) {
        if (root != NULL) {
            cout << root->data << " ";
            printPreorder(root->left);
            printPreorder(root->right);
        }
    }
    void printPostorder(node<T1, T2> *root) {
        if (root != NULL) {
            printPostorder(root->left);
            printPostorder(root->right);
            cout << root->data << " ";
        }
    }
    void deleteInPostorder(node<T1, T2> *root) {
        if (root != NULL) {
            deleteInPostorder(root->left);
            deleteInPostorder(root->right);
            nodeCount--;
            cout << "deleting " << root->data << endl;
            delete root;
        }
    }

    void printLevelorder(node<T1, T2> *root) {
        T1 def_val1 = {};
        T2 def_val2 = {};
        if (root == NULL) {
            return;
        }
        queue<node<T1, T2> *> q;
        q.push(root);
        while (!q.empty()) {
            node<T1, T2> *curr = q.front();
            q.pop();
            if (curr->data != def_val1)
                cout << curr->data << " ";
            else
                cout << "N ";
            if (curr->left != NULL)
                q.push(curr->left);
            else if (curr->data != def_val1) {
                node<T1, T2> *myNode = new node<T1, T2>(def_val1, def_val2);
                q.push(myNode);
            }
            if (curr->right != NULL)
                q.push(curr->right);
            else if (curr->data != def_val1) {
                node<T1, T2> *myNode = new node<T1, T2>(def_val1, def_val2);
                q.push(myNode);
            }
        }
    }

    T1 findMax(node<T1, T2> *root) {
        // assuming it is not called with null root
        if (root->right == NULL) {
            return root->data;
        }
        return findMax(root->right);
    }

    T1 findMin(node<T1, T2> *root) {
        // assuming it is not called with null root
        if (root->left == NULL) {
            return root->data;
        }
        return findMin(root->left);
    }

    node<T1, T2> *recursiveRemove(node<T1, T2> *root, T1 x) {
        if (root == NULL) {
            // simply return NULL...No tension :P
            return root;
        }
        if (cmp(root->data, x)) {
            // root->data is lesser than x
            // x > root->data
            root->right = recursiveRemove(root->right, x);
        } else if (cmp(x, root->data)) {
            // root->data is greater than x
            // x < root->data
            root->left = recursiveRemove(root->left, x);
        } else {
            // we got the node to be removed
            if (root->left == NULL) {
                // no right subtree
                return root->right;
            } else if (root->right == NULL) {
                // no left subtree
                return root->left;
            } else {
                if (root->left->height > root->right->height) {
                    T1 successorValue = findMax(root->left);
                    root->data = successorValue;
                    root->left = recursiveRemove(root->left, successorValue);
                } else {
                    T1 successorValue = findMin(root->right);
                    root->data = successorValue;
                    root->right = recursiveRemove(root->right, successorValue);
                }
            }
        }
        update(root);
        return balance(root);
    }

  public:
    int height() {
        // height of the tree is nothing but height of the root node
        if (gRoot == NULL) {
            return 0;
        }
        return gRoot.height;
    }

    int size() {
        // return the node count
        return nodeCount;
    }

    void insert(T1 d, T2 x) {
        nodeCount++;
        node<T1, T2> *newNodePtr = new node<T1, T2>(d, x);
        node<T1, T2> *rootPtr = gRoot;
        gRoot = recursiveInsert(rootPtr, newNodePtr);
    }

    void inorderTraversal() {
        node<T1, T2> *rootPtr = gRoot;
        cout << "[";
        printInorder(rootPtr);
        cout << "]" << endl;
    }

    void preorderTraversal() {
        node<T1, T2> *rootPtr = gRoot;
        cout << "[";
        printPreorder(rootPtr);
        cout << "]" << endl;
    }

    void postorderTraversal() {
        node<T1, T2> *rootPtr = gRoot;
        cout << "[";
        printPostorder(rootPtr);
        cout << "]" << endl;
    }

    void levelorderTraversal() {
        node<T1, T2> *rootPtr = gRoot;
        cout << "[";
        printLevelorder(rootPtr);
        cout << "]" << endl;
    }

    bool find(T1 x) {
        node<T1, T2> *rootPtr = gRoot;
        node<T1, T2> *nodePtr = recursiveSearch(rootPtr, x);
        if (nodePtr == NULL) {
            cout << "Key not found" << endl;
            return false;
        } else {
            cout << "Key found" << endl;
            return true;
        }
        return false;
    }

    void clear() {
        node<T1, T2> *rootPtr = gRoot;
        cout << "Clearing the tree..." << endl;
        deleteInPostorder(rootPtr);
    }

    T2 &operator[](T1 x) {
        node<T1, T2> *rootPtr = gRoot;
        node<T1, T2> *nodePtr = recursiveSearch(rootPtr, x);
        if (nodePtr == NULL) {
            T2 def_val2 = {};
            node<T1, T2> *newNodePtr = new node<T1, T2>(x, def_val2);
            gRoot = recursiveInsert(rootPtr, newNodePtr);
            rootPtr = gRoot;
            nodePtr = recursiveSearch(rootPtr, x);
        }
        return nodePtr->value;
    }

    void erase(T1 x) {
        if (find(x)) {
            node<T1, T2> *rootPtr = gRoot;
            gRoot = recursiveRemove(gRoot, x);
            nodeCount--;
            return;
        }
        cout << "Cannot remove...key not present" << endl;
    }
};

int main() { return 0; }