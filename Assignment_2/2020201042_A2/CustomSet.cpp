// This code's author is Rahul Valluri
// https://repl.it/@rahulv4667/CustomSet#main.cpp
#include <iostream>
using namespace std;

template <class T> class Node {
  public:
    T key;
    Node *left;
    Node *right;
    Node(T k) : key(k), left(NULL), right(NULL) {}
};

// Custom comparator
template <class T> struct Less {
    bool operator()(const T &lhs, const T &rhs) {
        // Datatype T must have operator< defined. Otherwise, this fails.
        return lhs < rhs;
    }
};

template <class T> struct Greater {
    bool operator()(const T &lhs, const T &rhs) {
        // Datatype T must have operator> defined. Otherwise, this fails.
        return lhs > rhs;
    }
};

// The comparator structure is taken as template argument.
template <class T, class Comparator = Less<T>> class CustomSet {
  private:
    Node<T> *gRoot;

    // an instance of comparator structure is stored.
    Comparator cmp;

    Node<T> *_insert(Node<T> *root, Node<T> *node) {
        if (root == NULL) {
            root = node;
            return root;
        }

        // cmp(a, b) checks whether a should come before b in the order.
        if (cmp(root->key, node->key))
            root->right = _insert(root->right, node);

        // cmp(b, a) to check if b should come before a
        else if (cmp(node->key, root->key))
            root->left = _insert(root->left, node);

        // will reach here when both are equal. u can insert the node in either
        // left or right if multiset. if normal set, directly return.
        else
            root->left = _insert(root->left, node);

        return root;
    }

    void _inorder(Node<T> *root) {
        if (!root)
            return;
        _inorder(root->left);
        cout << root->key << ", ";
        _inorder(root->right);
    }

  public:
    CustomSet() : gRoot(NULL), cmp(Comparator()) {
        // see above that an object of Comparator structure is initialized.
    }

    void insert(T key) {
        Node<T> *node = new Node<T>(key);
        Node<T> *root = gRoot;
        gRoot = _insert(root, node);
    }

    void inorderPrint() {
        Node<T> *root = gRoot;
        cout << " { ";
        _inorder(root);
        cout << " } \n";
    }
};

int main() {
    CustomSet<int> c;
    for (int i = 0; i < 10; i++)
        c.insert(i);
    c.inorderPrint();

    // providing different comparator than default
    CustomSet<int, Greater<int>> c1;
    for (int i = 10; i > 0; i--)
        c1.insert(i);
    c1.inorderPrint();
}