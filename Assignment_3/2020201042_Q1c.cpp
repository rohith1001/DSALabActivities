#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestPalindrome(string s) {
    if (s.size() <= 1) {
        return s.size();
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
        if (len > maxLen) {
            maxLen = len;
            start = l + 1;
            end = r - 1;
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
        if (len > maxLen) {
            maxLen = len;
            start = l + 1;
            end = r - 1;
        }
    }
    return maxLen;
}

int main() {
    string myStr;
    cin >> myStr;
    int x = lengthOfLongestPalindrome(myStr);

    cout << x << endl;

    return 0;
}
