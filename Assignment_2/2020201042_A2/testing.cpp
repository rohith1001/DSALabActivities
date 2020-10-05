#include <iostream>
using namespace std;

template <typename T1, typename T2> class A {
  public:
    void display(string x) {
        cout << "Displaying string" << endl;
        cout << x << endl;
    }

    void display(int x) {
        cout << "Displaying int" << endl;
        cout << x << endl;
    }
};

int main() {
    string s = "abc";
    int i = 99;
    A<string, int> a;
    a.display(s);
    A<int, int> b;
    b.display(99);
}