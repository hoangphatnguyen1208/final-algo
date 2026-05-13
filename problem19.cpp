#include <bits/stdc++.h>

using namespace std;
#define int long long


const int MAXN = 1e5 + 5;
int n, t;
int h[MAXN];

bool check(int mid) {
    vector <int> exp_r(n+1, 0), ans_r(n+1, 0);
    int active = 0;
    int sum = 0;

    for (int i = 0; i < n; i++) {
        active -= exp_r[i];
        sum -= active;
        int E_k = h[i] - mid;

        if (E_k > 0) {
            sum += E_k;
            active++;

            int idx = i + E_k + 1;
            if (idx <= n) {
                exp_r[idx]++;
            }
        }
        ans_r[i] = sum;
    }

    vector <int> exp_l(n+1, 0), ans_l(n+1, 0);
    active = 0;
    sum = 0;
    for (int i = n-1; i >= 0; i--) {
        active -= exp_l[i+1];
        sum -= active;
        int E_k = h[i] - mid;

        if (E_k > 0) {
            sum += E_k;
            active++;

            int idx = i - E_k - 1;
            if (idx >= 0) {
                exp_l[idx]++;
            }
        }
        ans_l[i] = sum;
    }

    for (int i = 0; i < n; i++) {
        if (ans_l[i] + ans_r[i] - (h[i] - mid) <= t) {
            return true;
        }
    }
    return false;
}

int32_t main() {
    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    int l = -1e18, r = 1e18;
    int ans = -1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
    return 0;
}