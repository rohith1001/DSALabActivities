#include <iostream>
using namespace std;

template <typename T1, typename T2> struct myPair {
    T1 key;
    T2 value;
    struct myPair<T1, T2> *next = NULL;
};

int main() {
    struct myPair<int, int> h1 = {
        .key = 10, .value = 20, .next = NULL
    };
    struct myPair<int, int> h2 = {
        .key = 30, .value = 20, .next = NULL
    };
    struct myPair<int, int> h3 = {
        .key = 40, .value = 20, .next = NULL
    };

    struct myPair<int, int> *table[2] = {}; // initializes to null
    struct myPair<int, int> *myPtr;

    cout << "Here" << endl;

    myPtr = &h1; // node to insert
    if (table[0] == NULL) {
        table[0] = myPtr;
        cout << "Successfully inserted" << endl;
    }
    myPtr = table[0];

    while (myPtr->next != NULL) {
        myPtr = myPtr->next;
    }
    myPtr->next = &h2;
    myPtr = table[0];

    while (myPtr->next != NULL) {
        myPtr = myPtr->next;
    }
    myPtr->next = &h3;
    myPtr = table[0];

    while (myPtr != NULL) {
        cout << "Key: " << myPtr->key << endl;
        cout << "Value: " << myPtr->value << endl;
        myPtr = myPtr->next;
    }
    return 0;
}