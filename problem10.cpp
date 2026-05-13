#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

int a[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    int n, m;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    int ans = 1;

    for (int i = 0; i < m; i++) {
        dp[i][0] = 1;
    }

    for (int j = 0; j < n; j++) {
        dp[0][j] = 1;
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = 1;
            if (a[i][j] == a[i-1][j] && a[i][j] == a[i][j-1] && a[i][j] == a[i-1][j-1]) {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                ans = max(ans, dp[i][j]);
            }
        }
    }
    cout << ans;
    return 0;
}