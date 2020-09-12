#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s, a;
    cin >> s >> a;
    cout << "Entered string s is: " << s << endl;
    cout << "Entered string a is: " << a << endl;
    reverse(s.begin(), s.end());
    cout << "Reversed string is: " << s << endl;
    return 0;
}