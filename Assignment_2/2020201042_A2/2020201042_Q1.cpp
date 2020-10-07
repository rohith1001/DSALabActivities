#include <iostream>
using namespace std;

template <typename T> class node {
  public:
    T data;
    int height;
    int balanceFactor;
    node *left;
    node *right;

    node(T x) {
        data = x;
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

template <typename T, typename Comparator = lesser<T>> class myAVLTree {
    node<T> *gRoot = NULL;
    int nodeCount = 0;
    Comparator cmp;

  private:
    void update(node<T> *nodePtr) {
        int leftSubTreeHeight = (nodePtr->left == NULL) ? -1 : nodePtr->left->height;
        int rightSubTreeHeight = (nodePtr->right == NULL) ? -1 : nodePtr->right->height;

        nodePtr->height = max(leftSubTreeHeight, rightSubTreeHeight) + 1;
        cout << "height updated to: " << nodePtr->height << endl;
        nodePtr->balanceFactor = leftSubTreeHeight - rightSubTreeHeight;
        cout << "balance factor updated to: " << nodePtr->balanceFactor << endl;
    }

    node<T> *balance(node<T> *nodePtr) {
        cout << "Balance is called" << endl;
        if (nodePtr->balanceFactor == 2) {
            // left heavy subtree
            cout << "It is left heavy" << endl;
            cout << "BF: " << nodePtr->balanceFactor << endl;
            if (nodePtr->left->balanceFactor >= 0) {
                return leftLeftCase(nodePtr);
            } else {
                return leftRightCase(nodePtr);
            }
        } else if (nodePtr->balanceFactor == -2) {
            cout << "Its a right heavy subtree" << endl;
            cout << "BFF:" << nodePtr->balanceFactor << endl;
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
            cout << "The data is: " << myNode->data << endl;
            root = myNode;
            return root;
        }
        // if root is not NULL
        cout << "Comparing " << root->data << " with " << myNode->data << endl;
        if (cmp(root->data, myNode->data)) {
            cout << "Yes root->data is lesser" << endl;
            // this means root->data is less than myNode->data
            // or in other words, myNode->data is greater than root->data
            // of course go to the right subtree
            root->right = recursiveInsert(root->right, myNode);
        } else {
            cout << "No root->data is greater" << endl;
            // this means root->data is greater than or equal to myNode->data
            // or in other words myNode->data <= root->data
            // so simply add it to the left subtree
            root->left = recursiveInsert(root->left, myNode);
        }
        // for updating the balanceFactor and height of the node
        update(root);

        // balance the tree if it is unbalanced
        return balance(root);
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
            printPreorder(root->left);
            printPreorder(root->right);
            cout << root->data << " ";
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
};

int main() {
    myAVLTree<char> myTree;
    for (int i = 97; i < 103; i++) {
        char ch = (char)i;
        myTree.insert(i);
        myTree.inorderTraversal();
        myTree.preorderTraversal();
        myTree.postorderTraversal();
    }
    return 0;
}