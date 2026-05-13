#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;

int dp[MAXN][MAXN];
int n, m, k;
pair<int, int> a[MAXN];

int main() {
    cin >> k >> n >> m;
    for (int i = 0; i < k; i++) {
        cin >> a[i].first >> a[i].second;
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = INT_MIN;
        }
    }
    dp[0][0] = 0;

    for (int idx = 0; idx < k; idx++) {
        int x = a[idx].first;
        int y = a[idx].second;

        for (int i = n; i >= 0; i--) {
            for (int j = m; j >= 0; j--) {
                if (i-1 >= 0) dp[i][j] = max(dp[i][j], dp[i-1][j] + x);
                if (j-1 >= 0) dp[i][j] = max(dp[i][j], dp[i][j-1] + y);
            }
        }
    }

    cout << dp[n][m];
    return 0;
}