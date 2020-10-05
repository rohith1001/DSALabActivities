#include <iostream>
#define TABLE_SIZE 10
#define BASE (long long)3
#define INITIAL_VALUE (long long)7
#define MACHINE_WORD (long long)64
#define ODD_POSITIVE (long long)7
#define BITS_IN_TABLE_SIZE (long long)1
using namespace std;

template <typename T1, typename T2> struct myPair {
    T1 key;
    T2 value;
    struct myPair<T1, T2> *next = NULL;
};

template <typename T1, typename T2> class unordered_map {
    struct myPair<T1, T2> *hashTable[TABLE_SIZE] = {};

  public:
    unordered_map() { hashTable[TABLE_SIZE] = {}; }

    long long hashFunction(string key) {
        long long x = INITIAL_VALUE;
        long long a = BASE;
        for (auto ch : key) {
            x = ((x * a) + (int)ch) % TABLE_SIZE;
        }
        cout << "String hash is returning: " << x << endl;
        return (x % TABLE_SIZE);
    }

    long long hashFunction(int key) {
        long long a = ODD_POSITIVE;
        long long w = MACHINE_WORD;
        long long M = BITS_IN_TABLE_SIZE;
        long long h = (size_t)(a * key) >> (w - M);
        cout << "Int hash is returning: " << h << endl;
        return h;
    }

    void insert(T1 k, T2 v) {
        long long index = hashFunction(k);
        if (hashTable[index] == NULL) {
            // simply insert the node in this case
            struct myPair<T1, T2> *p = new myPair<T1, T2> {
                .key = k, .value = v, .next = NULL
            };

            hashTable[index] = p;
        } else {
            struct myPair<T1, T2> *myPtr;
            myPtr = hashTable[index];
            while (myPtr->next != NULL) {
                cout << myPtr->key << endl;
                cout << "OMG! Struck here." << endl;
                if (myPtr->key == k) {
                    // simply update the value
                    myPtr->value = v;
                    break;
                }
                myPtr = (myPtr->next);
            }

            if (myPtr->next == NULL) {
                // myPtr->next is NULL now
                if (myPtr->key == k) {
                    myPtr->value = v;
                } else {
                    struct myPair<T1, T2> *p = new myPair<T1, T2> {
                        .key = k, .value = v, .next = NULL
                    };

                    myPtr->next = p;
                }
            }
        }
        cout << "Successfully exiting insert" << endl;
    }

    void erase(T1 key);

    bool find(T1 key);

    T1 &operator[](long long n);

    void printTable() {
        for (long long i = 0; i < TABLE_SIZE; i++) {
            if (hashTable[i] != NULL) {
                cout << i << ": ---> ";
                struct myPair<T1, T2> *nodePtr;
                nodePtr = hashTable[i];
                // nodePtr is pointing to the same place where hashTable[i] is pointing
                while (nodePtr != NULL) {
                    cout << "[" << nodePtr->key << "]: " << nodePtr->value << " ";
                    nodePtr = nodePtr->next;
                }
                cout << endl;
            }
        }
    }
};

int main() {
    unordered_map<int, int> a;
    a.insert(2, 2);
    a.insert(3, 3);
    a.printTable();
    return 0;
}
