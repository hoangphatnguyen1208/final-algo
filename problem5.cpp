#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;
int lps[MAXN];
string a, b;

void buildLPS() {
    int n = b.size();

    int i = 1, len = 0;
    while (i < n) {
        if (b[i] == b[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len-1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main() {
    cin >> a >> b;
    buildLPS();
    int len = 0;
    int ans = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[len]) {
            len++;
            if (len == b.size()) {
                cout << i - len + 2 << ' ';
                len = lps[len-1];
            }
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
                i--;
            }
        }
    }
    return 0;
}