#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;
const int LOG = 20;

int st[MAXN][LOG];
int lg[MAXN];
int a[MAXN];
int n, k;

int get_gcd(int l, int r) {
    int j = lg[r-l+1];
    return __gcd(st[l][j], st[r-(1<<j)+1][j]);
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i/2] + 1;
    }

    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; i + (1 << j) <= n; j++) {
            st[i][j] = __gcd(st[i][j-1], st[i+(1<<(j-1))][j-1]);
        }
    }

    int ans = 0;
    for (int i = k; i <= n; i++) {
        ans = max(ans, get_gcd(i-k+1, i));
    }
    cout << ans;
    return 0;
}
