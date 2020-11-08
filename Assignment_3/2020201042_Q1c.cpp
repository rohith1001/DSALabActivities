#include <bits/stdc++.h>
using namespace std;

string findLongestPalindrome(string s) {
    string ans;
    if (s.size() <= 1) {
        return s;
    }
    int maxLen = 1;
    int n = s.size();
    int start = 0, end = 0;

    for (int i = 0; i < n - 1; i++) {
        int l = i, r = i;
        while (l >= 0 && r < n) {
            if (s[l] == s[r]) {
                l--;
                r++;
            } else
                break;
        }

        int len = r - l - 1;
        if (len == maxLen) {
            if ((s.substr(l + 1, maxLen)) < ans) {
                ans = s.substr(l + 1, maxLen);
            }
        }
        if (len > maxLen) {
            maxLen = len;

            start = l + 1;
            end = r - 1;
            ans = (s.substr(start, maxLen));
        }
    }

    for (int i = 0; i < n - 1; i++) {
        int l = i, r = i + 1;
        while (l >= 0 && r < n) {
            if (s[l] == s[r]) {
                l--;
                r++;
            } else
                break;
        }

        int len = r - l - 1;
        if (len == maxLen) {
            if ((s.substr(l + 1, maxLen)) < ans) {
                ans = s.substr(l + 1, maxLen);
            }
        }
        if (len > maxLen) {
            maxLen = len;

            start = l + 1;
            end = r - 1;
            ans = (s.substr(start, maxLen));
        }
    }
    return ans;
}

int main() {
    string myStr;
    cin >> myStr;
    string x = findLongestPalindrome(myStr);

    cout << x << endl;

    return 0;
}
