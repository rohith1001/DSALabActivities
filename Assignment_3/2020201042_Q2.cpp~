#include <iostream>
using namespace std;

struct TrieNode {
    TrieNode *child[2] = {};
    TrieNode() {
        child[0] = NULL;
        child[1] = NULL;
    }
};

void insert(struct TrieNode *myRoot, unsigned long long x, int checkbit) {
    // converting number to 40 bits in binary, so initially 40 is passed to checkbit
    if (checkbit < 0) {
        return;
    }

    int k = (x >> checkbit) & 1; // just check if the "checkbit" is set or not
    if (myRoot->child[k] == NULL) {
        myRoot->child[k] = new struct TrieNode();
    }
    insert(myRoot->child[k], x, checkbit - 1);
}

void search(struct TrieNode *myRoot, unsigned long long key, int checkbit, unsigned long long &maxVal) {
    if (checkbit < 0)
        return;

    int k = (key >> checkbit) & 1; // checks if the checkbit is set
    k = (k ^ 1);                   // inverting the bit, xor with 1 inverts the bit

    if (myRoot->child[k] == NULL) {
        k = (k ^ 1); // invert the bit
    }
    // we are converting every single array element into 40 bits
    // maxVal = (maxVal * 2) + power(2,k) if k = 1
    // maxVal = (maxVal * 2) + 0 if k = 0
    maxVal = (maxVal << 1) | k;
    search(myRoot->child[k], key, checkbit - 1, maxVal);
}

int main() {
    long long n, q;
    cin >> n >> q;
    struct TrieNode *myTrie = new struct TrieNode();
    for (long long i = 0; i < n; i++) {
        unsigned long long x;
        cin >> x;
        insert(myTrie, x, 40);
    }

    while (q--) {
        long long key;
        cin >> key;
        unsigned long long maxVal = 0;
        search(myTrie, key, 40, maxVal);
        cout << (maxVal ^ key) << endl;
    }
    return 0;
}
