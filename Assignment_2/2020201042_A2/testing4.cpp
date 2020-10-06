#include <bits/stdc++.h>
using namespace std;

int main() {
    unordered_map<string, string> m;
    if (m["a"] != "") {
        cout << "m[0] is: " << m["a"] << endl;
    } else {
        cout << "In else: " << m["a"] << endl;
    }
    cout << "This is how null looks like..." << endl;
    string s = {};
    cout << s << endl;
    return 0;
}