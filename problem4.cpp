#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;
int n;
int a[MAXN];

long long merge_sort(int l, int r) {
    if (l >= r) return 0;

    int mid = l + r >> 1;
    long long ans = 0;
    ans += merge_sort(l, mid);
    ans += merge_sort(mid+1, r);

    

}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }


    return 0;
}