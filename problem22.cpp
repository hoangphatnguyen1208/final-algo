// Time: O(N+M)
// Space: O(N+M)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
struct Edge {
    int to, id;
};

vector<Edge> adj[MAXN];
int tin[MAXN], low[MAXN], subtree_size[MAXN], comp_size[MAXN];
long long results[200005]; // Lưu kết quả cho từng cạnh theo ID
bool visited[MAXN];
int timer;

// Hàm tính kích thước của từng thành phần liên thông ban đầu
int get_size(int u) {
    visited[u] = true;
    int sz = 1;
    for (auto& edge : adj[u]) {
        if (!visited[edge.to]) {
            sz += get_size(edge.to);
        }
    }
    return sz;
}

// Hàm DFS tìm cầu và tính toán số cặp bị ngắt kết nối
void dfs(int u, int p_edge_id, int total_s) {
    visited[u] = true;
    tin[u] = low[u] = ++timer;
    subtree_size[u] = 1;
    
    for (auto& edge : adj[u]) {
        if (edge.id == p_edge_id) continue;
        if (visited[edge.to]) {
            low[u] = min(low[u], tin[edge.to]);
        } else {
            dfs(edge.to, edge.id, total_s);
            subtree_size[u] += subtree_size[edge.to];
            low[u] = min(low[u], low[edge.to]);
            
            // Kiểm tra nếu cạnh là cầu
            if (low[edge.to] > tin[u]) {
                long long s1 = subtree_size[edge.to];
                long long s2 = total_s - s1;
                results[edge.id] = s1 * s2;
            } else {
                results[edge.id] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    // Xử lý từng thành phần liên thông (đề phòng đồ thị không liên thông từ đầu)
    fill(visited, visited + n + 1, false);
    vector<pair<int, int>> components;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            int sz = get_size(i);
            components.push_back({i, sz});
        }
    }

    fill(visited, visited + n + 1, false);
    timer = 0;
    for (auto& comp : components) {
        dfs(comp.first, -1, comp.second);
    }

    for (int i = 0; i < m; ++i) {
        cout << results[i] << "\n";
    }

    return 0;
}