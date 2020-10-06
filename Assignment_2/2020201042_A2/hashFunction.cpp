#include <iostream>
#define TABLE_SIZE 101
using namespace std;
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

long long hashFunction(char key) {
    unsigned long long int initial_value_x;
    initial_value_x = (int)key % TABLE_SIZE;
    return (initial_value_x % TABLE_SIZE);
}

long long hashFunction(string key) {
    unsigned long long initial_value_x = 0;
    unsigned long long base_a = 256;
    for (auto ch : key) {
        initial_value_x = ((initial_value_x * base_a) + (int)ch) % TABLE_SIZE;
    }
    return (initial_value_x % TABLE_SIZE);
}

int main() {

    for (int i = 0; i <= 20; i++) {
        cout << "i: " << hashFunction(i) << endl;
    }

    cout << hashFunction('a') << endl;
    cout << hashFunction('b') << endl;
    cout << hashFunction('c') << endl;

    return 0;
}
