#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int n;
int a[MAXN], lmax[MAXN], rmax[MAXN];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    lmax[0] = a[0];
    for (int i = 1; i < n; i++) {
        lmax[i] = max(lmax[i-1], a[i]);
    }

    rmax[n-1] = a[n-1];
    for (int i = n - 2; i >= 0; i--) {
        rmax[i] = max(rmax[i+1], a[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += min(lmax[i], rmax[i]) - a[i];
    }
    cout << ans;

    return 0;
}