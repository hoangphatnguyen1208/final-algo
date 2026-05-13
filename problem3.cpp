#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector <pair<int, int>> a, b;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back({x, i+1});
    }
    for (int j = 0; j < n; j++) {
        int x;
        cin >> x;
        b.push_back({x, j+1});
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int mn = INT_MAX;
    int ii, jj;
    for (int i = 0; i < a.size(); i++) {
        int j = upper_bound(b.begin(), b.end(), make_pair(-a[i].first, -1)) - b.begin();
        if (mn > abs(a[i].first + b[j].first)) {
            mn = abs(a[i].first + b[j].first);
            ii = a[i].second;
            jj = b[j].second;
        }
        if (j-1 >= 0 && mn > abs(a[i].first + b[j-1].first)) {
            mn = abs(a[i].first + b[j-1].first);
            ii = a[i].second;
            jj = b[j-1].second;
        } 
    }
    cout << ii << ' ' << jj;
    return 0;
}