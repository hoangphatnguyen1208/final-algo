// time: O(n) với n là số đỉnh của cây
// space: O(n) cho mảng lưu kích thước cây con

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1005;
vector<int> adj[MAXN];
long long subtree_size[MAXN];
long long total_width = 0;
int n;

// Hàm DFS để tính kích thước cây con và tổng đóng góp của cạnh
void dfs(int u, int p) {
    subtree_size[u] = 1; // Bản thân đỉnh u
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        subtree_size[u] += subtree_size[v];
        
        // Cạnh nối (u, v) chia cây thành 2 phần:
        // Phần 1: cây con gốc v (kích thước subtree_size[v])
        // Phần 2: phần còn lại (kích thước n - subtree_size[v])
        total_width += subtree_size[v] * (n - subtree_size[v]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n)) return 0;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (n > 0) {
        dfs(1, 0);
    }

    cout << total_width << endl;

    return 0;
}