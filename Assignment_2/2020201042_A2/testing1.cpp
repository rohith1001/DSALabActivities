#include <iostream>
using namespace std;

template <typename T1, typename T2> struct myPair {
    T1 key;
    T2 value;
    struct myPair<T1, T2> *next = NULL;
};

template <typename T1, typename T2> class unordered_map {
    struct myPair<T1, T2> *hashTable[10];

  public:
    void insert(T1 k, T2 v) {
        if (hashTable[0] == NULL) {
            struct myPair<T1, T2> p = {
                .key = k, .value = v, .next = NULL
            };
            hashTable[0] = &p;
        } else {
            cout << "hashTable[" << 0 << "] is not NULL" << endl;
            // traverse the chain till you hit NULL
            struct myPair<T1, T2> *nodePtr;
            nodePtr = hashTable[0];
            cout << "Key: " << nodePtr->key << endl;
            cout << "Value: " << nodePtr->value << endl;

            while (nodePtr->next != NULL && nodePtr->key != k) {
                // cout << "Stuck here" << endl;
                struct myPair<T1, T2> *tempPtr;
                tempPtr = nodePtr->next;
                nodePtr = tempPtr;
            }

            if (nodePtr->key == k) {
                cout << "Warning updating the value of key: " << k << endl;
                nodePtr->value = v;
            } else {
                // nodePtr->next is NULL now
                struct myPair<T1, T2> p = {
                    .key = k, .value = v, .next = NULL
                };
                cout << "Node pointer is null now" << endl;
                nodePtr->next = &p;
                cout << "successfully inserted key value at " << 0 << endl;
            }
        }
    }

    void printTable() {
        cout << "Trying to print the table..." << endl;
        for (long long i = 0; i < 10; i++) {
            if (hashTable[i] != NULL) {
                cout << "i is: " << i << ":" << endl;
                struct myPair<T1, T2> *nodePtr;
                nodePtr = hashTable[i];
                // nodePtr is pointing to the same place where hashTable[i] is pointing
                cout << "Jai Makalamma!!!" << endl;
                if (nodePtr != NULL) {
                    cout << "Be happy nodePtr not null" << endl;
                }
                cout << "Key is: " << nodePtr->key << endl;
                cout << "Value is: " << nodePtr->value << endl;
                cout << "[" << nodePtr->key << "]: " << nodePtr->value << " ";
                // while (nodePtr != NULL) {
                //     cout << "[" << nodePtr->key << "]: " << nodePtr->value << " ";
                //     nodePtr = nodePtr->next;
                // }
            }
        }
    }
};

int main() {
    unordered_map<int, int> a;
    a.insert(1, 1);
    a.insert(2, 2);
    a.insert(3, 3);
    a.printTable();
    return 0;
}