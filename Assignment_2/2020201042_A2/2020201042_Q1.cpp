#include <bits/stdc++.h>
#include <iostream>
using namespace std;

template <typename T> class node {
  public:
    T data;
    int height;
    int balanceFactor;
    int duplicateCount = 0;
    node *left;
    node *right;

    node(T x) {
        data = x;
        height = 0;
        balanceFactor = 0;
        duplicateCount = 1;
        left = NULL;
        right = NULL;
    }
};

template <class T> struct lesser {
    // my custom comparator
    // this will be our default comparator to build our BST
    bool operator()(const T &l, const T &r) { return l < r; }
};

template <typename T, typename Comparator = lesser<T>> class myAVLTree {
    node<T> *gRoot = NULL;
    int nodeCount = 0;
    Comparator cmp;

  private:
    void update(node<T> *nodePtr) {
        int leftSubTreeHeight = (nodePtr->left == NULL) ? -1 : nodePtr->left->height;
        int rightSubTreeHeight = (nodePtr->right == NULL) ? -1 : nodePtr->right->height;
        nodePtr->height = max(leftSubTreeHeight, rightSubTreeHeight) + 1;
        nodePtr->balanceFactor = leftSubTreeHeight - rightSubTreeHeight;
    }

    node<T> *balance(node<T> *nodePtr) {
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

    node<T> *leftLeftCase(node<T> *nodePtr) { return rightRotation(nodePtr); }

    node<T> *leftRightCase(node<T> *nodePtr) {
        nodePtr->left = leftRotation(nodePtr->left);
        return leftLeftCase(nodePtr);
    }

    node<T> *rightLeftCase(node<T> *nodePtr) {
        nodePtr->right = rightRotation(nodePtr->right);
        return rightRightCase(nodePtr);
    }

    node<T> *rightRightCase(node<T> *nodePtr) { return leftRotation(nodePtr); }

    node<T> *leftRotation(node<T> *nodePtr) {
        node<T> *newParent = nodePtr->right;
        nodePtr->right = newParent->left;
        newParent->left = nodePtr;
        update(nodePtr);
        update(newParent);
        return newParent;
    }

    node<T> *rightRotation(node<T> *nodePtr) {
        node<T> *newParent = nodePtr->left;
        nodePtr->left = newParent->right;
        newParent->right = nodePtr;
        update(nodePtr);
        update(newParent);
        return newParent;
    }

    node<T> *recursiveInsert(node<T> *root, node<T> *myNode) {
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
            update(root->right);
        } else if (cmp(myNode->data, root->data)) {
            // this means root->data is greater than myNode->data
            // or in other words myNode->data <= root->data
            // so simply add it to the left subtree
            root->left = recursiveInsert(root->left, myNode);
            update(root->left);
        } else {
            // its a duplicate entry
            // root->data = myNode->data
            cout << "Duplicates...recorded" << endl;
            (root->duplicateCount)++;
        }
        // for updating the balanceFactor and height of the node
        update(root);

        // balance the tree if it is unbalanced
        return balance(root);
    }

    node<T> *recursiveSearch(node<T> *root, T x) {
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

    void printInorder(node<T> *root) {
        if (root != NULL) {
            printInorder(root->left);
            cout << root->data << " ";
            printInorder(root->right);
        }
    }
    void printPreorder(node<T> *root) {
        if (root != NULL) {
            cout << root->data << " ";
            printPreorder(root->left);
            printPreorder(root->right);
        }
    }
    void printPostorder(node<T> *root) {
        if (root != NULL) {
            printPostorder(root->left);
            printPostorder(root->right);
            cout << root->data << " ";
        }
    }

    void printLevelorder(node<T> *root) {
        T def_val = {};
        if (root == NULL) {
            return;
        }
        queue<node<T> *> q;
        q.push(root);
        while (!q.empty()) {
            node<T> *curr = q.front();
            q.pop();
            if (curr->data != def_val)
                cout << curr->data << " ";
            else
                cout << "N ";
            if (curr->left != NULL)
                q.push(curr->left);
            else if (curr->data != def_val) {
                node<T> *myNode = new node<T>(def_val);
                q.push(myNode);
            }
            if (curr->right != NULL)
                q.push(curr->right);
            else if (curr->data != def_val) {
                node<T> *myNode = new node<T>(def_val);
                q.push(myNode);
            }
        }
    }

    node<T> *recursiveRemove(node<T> *root, T x) {
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
                    T successorValue = findMax(root->left);
                    root->data = successorValue;
                    root->left = recursiveRemove(root->left, successorValue);
                } else {
                    T successorValue = findMin(root->right);
                    root->data = successorValue;
                    root->right = recursiveRemove(root->right, successorValue);
                }
            }
        }
        update(root);
        return balance(root);
    }

    T findMax(node<T> *root) {
        // assuming it is not called with null root
        if (root->right == NULL) {
            return root->data;
        }
        return findMax(root->right);
    }

    T findMin(node<T> *root) {
        // assuming it is not called with null root
        if (root->left == NULL) {
            return root->data;
        }
        return findMin(root->left);
    }

    T absolute_difference(T a, T b) {
        if (cmp(a, b)) {
            return (T)(b - a);
        }
        return (T)(a - b);
    }

    void recursive_upperBound(node<T> *root, T x, T &ub) {
        // first element which is greater than or equal to the key
        if (root == NULL) {
            return;
        }
        if (cmp(x, root->data)) {
            ub = root->data;
            recursive_upperBound(root->left, x, ub);
        } else {
            recursive_upperBound(root->right, x, ub);
        }
    }

    void recursive_lowerBound(node<T> *root, T x, T &lb) {
        // first element which is greater than or equal to the key
        if (root == NULL) {
            return;
        }
        if (cmp(x, root->data) || (!cmp(x, root->data) && !cmp(root->data, x))) {
            lb = root->data;
            recursive_lowerBound(root->left, x, lb);
        } else {
            recursive_lowerBound(root->right, x, lb);
        }
    }

    void recursive_closestElement(node<T> *root, T x, T &c, T &d) {
        if (root == NULL) {
            return;
        }

        if (!cmp(root->data, x) && !(cmp(x, root->data))) {
            c = root->data;
            return;
        }

        if (cmp(absolute_difference(root->data, x), d)) {
            d = absolute_difference(root->data, x);
            c = root->data;
        }

        if (cmp(x, root->data)) {
            recursive_closestElement(root->left, x, c, d);
        } else {
            recursive_closestElement(root->right, x, c, d);
        }
    }

    void recursiveUpdate(node<T> *root) {
        if (root != NULL) {
            update(root->left);
            update(root->right);
        }
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

    void insert(T d) {
        nodeCount++;
        node<T> *newNodePtr = new node<T>(d);
        node<T> *rootPtr = gRoot;
        gRoot = recursiveInsert(rootPtr, newNodePtr);
    }

    void inorderTraversal() {
        node<T> *rootPtr = gRoot;
        cout << "[";
        printInorder(rootPtr);
        cout << "]" << endl;
    }

    void preorderTraversal() {
        node<T> *rootPtr = gRoot;
        cout << "[";
        printPreorder(rootPtr);
        cout << "]" << endl;
    }

    void postorderTraversal() {
        node<T> *rootPtr = gRoot;
        cout << "[";
        printPostorder(rootPtr);
        cout << "]" << endl;
    }

    void levelorderTraversal() {
        node<T> *rootPtr = gRoot;
        cout << "[";
        printLevelorder(rootPtr);
        cout << "]" << endl;
    }

    bool find(T x) {
        node<T> *rootPtr = gRoot;
        node<T> *nodePtr = recursiveSearch(rootPtr, x);
        if (nodePtr == NULL) {
            cout << "Key not found" << endl;
            return false;
        }
        cout << "Key found" << endl;
        return true;
    }

    void erase(T x) {
        node<T> *rootPtr = gRoot;
        node<T> *nodePtr = recursiveSearch(rootPtr, x);
        if (nodePtr != NULL) {
            if (nodePtr->duplicateCount > 1) {
                (nodePtr->duplicateCount)--;
            } else {
                gRoot = recursiveRemove(gRoot, x);
            }
            nodeCount--;
            return;
        }
        cout << "Cannot remove...key not present" << endl;
    }

    int countOccurrences(T x) {
        node<T> *rootPtr = gRoot;
        node<T> *nodePtr;
        nodePtr = recursiveSearch(rootPtr, x);
        if (nodePtr != NULL) {
            return nodePtr->duplicateCount;
        }
        return 0;
    }

    void lower_bound(T x) {
        // first element which is strictly greater than the key
        node<T> *rootPtr = gRoot;
        T lb = {};
        recursive_lowerBound(rootPtr, x, lb);
        cout << "Lower bound is: " << lb << endl;
    }

    void upper_bound(T x) {
        // first element which is greater than or equal to the key
        node<T> *rootPtr = gRoot;
        T ub = {};
        recursive_upperBound(rootPtr, x, ub);
        cout << "Upper bound is: " << ub << endl;
    }

    void closestElement(T x) {
        T c = {};
        T d = numeric_limits<T>::max();
        node<T> *rootPtr = gRoot;
        recursive_closestElement(rootPtr, x, c, d);
        cout << "Closest element: " << c << endl;
    }
};

int main() {
    myAVLTree<int> myTree;
    for (int i = 97; i < 103; i++) {
        myTree.insert(i);
    }
    myTree.levelorderTraversal();
    myTree.size();
    return 0;
}