#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef long long ll;

ll fact[21];

void precomputeFactorials() {
    fact[0] = 1;
    for (int i = 1; i <= 20; ++i) fact[i] = fact[i - 1] * i;
}

// Hàm tìm Rank từ Hoán vị
ll getRank(const vector<int>& p) {
    int n = p.size();
    ll rank = 0;
    vector<bool> used(n + 1, false);
    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int v = 1; v < p[i]; ++v) {
            if (!used[v]) count++;
        }
        rank += (ll)count * fact[n - 1 - i];
        used[p[i]] = true;
    }
    return rank + 1;
}

// Hàm tìm Hoán vị từ Rank
vector<int> getPermutation(int n, ll y) {
    ll r = y - 1;
    vector<int> p(n);
    vector<int> available;
    for (int i = 1; i <= n; ++i) available.push_back(i);

    for (int i = 0; i < n; ++i) {
        int idx = r / fact[n - 1 - i];
        p[i] = available[idx];
        available.erase(available.begin() + idx);
        r %= fact[n - 1 - i];
    }
    return p;
}

int main() {
    precomputeFactorials();

    // Đọc dòng 1: Hoán vị p
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> p;
    int val;
    while (ss >> val) p.push_back(val);
    int n = p.size();

    // Đọc dòng 2: Số thứ tự y
    ll y;
    cin >> y;

    // Kết quả 1: Rank x
    cout << getRank(p) << endl;

    // Kết quả 2: Hoán vị q
    vector<int> q = getPermutation(n, y);
    for (int i = 0; i < n; ++i) {
        cout << q[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}