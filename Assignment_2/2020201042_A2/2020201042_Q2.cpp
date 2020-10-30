#include <iostream>
#define TABLE_SIZE 1000
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
        unsigned long long initial_value_x = 0;
        unsigned long long base_a = 256;
        for (auto ch : key) {
            initial_value_x = ((initial_value_x * base_a) + (int)ch) % TABLE_SIZE;
        }
        return (initial_value_x % TABLE_SIZE);
    }

    long long hashFunction(char key) {
        unsigned long long initial_value_x = 0;
        initial_value_x = ((int)key % TABLE_SIZE);
        return (initial_value_x % TABLE_SIZE);
    }

    long long hashFunction(int key) {
        unsigned long long int myHash;
        unsigned long long int modulus_m = (1UL << 48);
        unsigned long long int multiplier_a = 25214903917;
        unsigned long long int increment_c = 11;
        if (key >= 0) {
            myHash = (multiplier_a * key + increment_c) % modulus_m;
        } else {
            myHash = (multiplier_a * (-1 * key) + increment_c) % modulus_m;
        }
        myHash = myHash % TABLE_SIZE;
        return myHash;
    }

    long long hashFunction(float key) {
        // hashing floating points is a bad idea
        int x = (int)key;
        return hashFunction(x);
    }

    long long hashFunction(double key) {
        // hashing floating points is a bad idea
        int x = (int)key;
        return hashFunction(x);
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
                if (myPtr->key == k) {
                    // simply update the value
                    myPtr->value = v;
                    cout << "Warning...updating value of a previous key,value" << endl;
                    return;
                }
                myPtr = (myPtr->next);
            }
            // control here means, myPtr->next is NULL
            // myPtr->next is NULL now
            if (myPtr->key == k) {
                // just checking the last element in the chain
                cout << "Warning...updating value of a previous key,value" << endl;
                myPtr->value = v;
            } else {
                struct myPair<T1, T2> *p = new myPair<T1, T2> {
                    .key = k, .value = v, .next = NULL
                };

                myPtr->next = p;
            }
        }
    }

    void erase(T1 k) {
        long long index = hashFunction(k);
        if (hashTable[index] == NULL) {
            // nothing doing :P
            return;
        }
        // hashTable[index] != NULL here
        if (hashTable[index]->key == k) {
            hashTable[index] = hashTable[index]->next;
            return;
        }
        // control here, means hashTable[index] is not null
        // and hashTable[index]->key != k
        struct myPair<T1, T2> *myPtr, *prevPtr;
        myPtr = hashTable[index];
        prevPtr = hashTable[index];
        while (myPtr->next != NULL) {
            if (myPtr->key == k) {
                prevPtr = myPtr->next;
                free(myPtr);
                return;
            }
            prevPtr = myPtr;
            myPtr = myPtr->next;
        }

        prevPtr->next = myPtr->next;
        free(myPtr);
        return;
    };

    bool find(T1 k) {
        long long index = hashFunction(k);
        if (hashTable[index] == NULL) {
            return false;
        }
        struct myPair<T1, T2> *myPtr;
        myPtr = hashTable[index];
        while (myPtr != NULL) {
            if (myPtr->key == k) {
                return true;
            }
            myPtr = myPtr->next;
        }
        return false;
    };

    T2 operator[](T1 k) {
        long long index = hashFunction(k);
        if (hashTable[index] == NULL) {
            T2 default_value = {};
            struct myPair<T1, T2> *p = new myPair<T1, T2> {
                .key = k, .value = {}, .next = NULL
            };
            hashTable[index] = p;
            return default_value;
        }

        // control here, means hashTable[index] is not null
        struct myPair<T1, T2> *myPtr;
        myPtr = hashTable[index];
        while (myPtr->next != NULL) {
            if (myPtr->key == k) {
                return myPtr->value;
            }
            myPtr = myPtr->next;
        }
        // hashed value caused a collision
        // but there is no element corresponding to the key
        // also if you're here that means myPtr->next is NULL
        T2 default_value = {};
        struct myPair<T1, T2> *p = new myPair<T1, T2> {
            .key = k, .value = {}, .next = NULL
        };
        myPtr->next = p;
        return default_value;
    };

    void printTable() {
        for (long long i = 0; i < TABLE_SIZE; i++) {
            if (hashTable[i] != NULL) {
                cout << i << ": ---> ";
                struct myPair<T1, T2> *nodePtr;
                nodePtr = hashTable[i];
                // nodePtr is pointing to the same place where hashTable[i] is pointing
                while (nodePtr != NULL) {
                    cout << "[" << nodePtr->key << "]: " << nodePtr->value << " ";
                    nodePtr = (nodePtr->next);
                }
                cout << endl;
            }
        }
    }
};

int main() { return 0; }
