#include <bits/stdc++.h>

using namespace std;

string s, p;
int dp[50][50];
int main() {
    cin >> s >> p;
    int n = s.size();
    int m = p.size();
    memset(dp, 0, sizeof(dp));

    dp[0][0] = 1;

    for (int j = 2; j <= m; j++) {
        if (p[j-1] == '*') {
            dp[0][j] = dp[0][j-2];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            
            if (p[j-1] == s[i-1] || p[j-1] == '.') {
                dp[i][j] = dp[i-1][j-1];
            }
            else {
                if (p[j-1] == '*') {
                    dp[i][j] = dp[i][j-2];

                    if (p[j-2] == s[i-1] || p[j-2] == '.') {
                        dp[i][j] = max(dp[i][j], dp[i-1][j]);
                    }
                }
            }
        }
    }

    cout << (dp[n][m]? "true" : "false");
    return 0;
}