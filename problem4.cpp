#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50005;
int n;
int a[MAXN], tmp[MAXN];

long long merge_sort(int left, int right) {
    if (left >= right) return 0;

    int mid = (left + right) >> 1;
    long long ans = 0;
    ans += merge_sort(left, mid);
    ans += merge_sort(mid+1, right);

    int i = left;
    int j = mid + 1;
    int k = left;
    
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        }
        else {
            tmp[k++] = a[j++];
            ans += mid-i+1;
        }
    }

    while (i <= mid) {
        tmp[k++] = a[i++];
    }

    while (j <= right) {
        tmp[k++] = a[j++];
    }

    for (int p = left; p <= right; p++) {
        a[p] = tmp[p];
    }
    return ans;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    cout << merge_sort(1, n);
    return 0;
}