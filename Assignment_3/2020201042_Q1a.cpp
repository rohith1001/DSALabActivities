#include <bits/stdc++.h>
using namespace std;

struct suffixNode {
    int index;
    int curRank;
    int nexRank;
};

bool cmp(struct suffixNode a, struct suffixNode b) {
    if (a.curRank == b.curRank) {
        if (a.nexRank < b.nexRank)
            return true;
    } else {
        if (a.curRank < b.curRank)
            return true;
    }
    return false;
}

int *computeSuffixArr(string myStr, int n) {
    struct suffixNode suffixTable[n];

    for (int i = 0; i < n; i++) {
        suffixTable[i].index = i;
        suffixTable[i].curRank = myStr[i] - 'a';
        if (i + 1 < n) {
            suffixTable[i].nexRank = myStr[i + 1] - 'a';
        } else {
            suffixTable[i].nexRank = -1;
        }
    }

    sort(suffixTable, suffixTable + n, cmp);

    int ind[n];
    for (int k = 4; k < 2 * n; k = k * 2) {
        int rank = 0;
        int prev_rank = suffixTable[0].curRank;
        suffixTable[0].curRank = rank;
        ind[suffixTable[0].index] = 0;

        for (int i = 1; i < n; i++) {
            if (suffixTable[i].curRank == prev_rank && suffixTable[i].nexRank == suffixTable[i - 1].nexRank) {
                prev_rank = suffixTable[i].curRank;
                suffixTable[i].curRank = rank;
            } else {
                prev_rank = suffixTable[i].curRank;
                rank++;
                suffixTable[i].curRank = rank;
            }
            ind[suffixTable[i].index] = i;
        }

        for (int i = 0; i < n; i++) {
            int nextIndex = suffixTable[i].index + k / 2;
            if (nextIndex < n) {
                suffixTable[i].nexRank = suffixTable[ind[nextIndex]].curRank;
            } else {
                suffixTable[i].nexRank = -1;
            }
        }

        sort(suffixTable, suffixTable + n, cmp);
    }

    int *suffixArr = new int[n];
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixTable[i].index;

    return suffixArr;
}

int main() {
    string myStr;
    cin >> myStr;

    int n = myStr.size();
    myStr += myStr;
    int *suffixArr = computeSuffixArr(myStr, 2 * n);

    int minLexIdx;
    for (int i = 0; i < 2 * n; i++) {
        if (suffixArr[i] < n) {
            minLexIdx = suffixArr[i];
            break;
        }
    }

    string res = myStr.substr(minLexIdx, n);
    cout << res << endl;
    return 0;
}
