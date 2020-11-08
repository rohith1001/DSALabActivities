#include <bits/stdc++.h>
using namespace std;

string findLongestPalindrome(string s) {
    vector<string> ans;
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
            ans.push_back(s.substr(l + 1, maxLen));
        }
        if (len > maxLen) {
            ans.clear();
            maxLen = len;

            start = l + 1;
            end = r - 1;
            ans.push_back(s.substr(start, maxLen));
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
            ans.push_back(s.substr(l + 1, maxLen));
        }
        if (len > maxLen) {
            ans.clear();
            maxLen = len;

            start = l + 1;
            end = r - 1;
            ans.push_back(s.substr(start, maxLen));
        }
    }
    sort(ans.begin(), ans.end());
    return ans[0];
}

int main() {
    string myStr;
    cin >> myStr;
    string x = findLongestPalindrome(myStr);

    cout << x << endl;

    return 0;
}
