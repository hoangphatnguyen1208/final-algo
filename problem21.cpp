#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

struct Edge {
    int u, v, w, id;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) { parent.resize(n + 1); for(int i=1; i<=n; ++i) parent[i] = i; }
    int find(int i) { return (parent[i] == i) ? i : (parent[i] = find(parent[i])); }
    bool unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) { parent[root_i] = root_j; return true; }
        return false;
    }
};

struct State {
    long long weight;
    vector<int> mst_edges_idx;
    vector<int> forced_idx;
    vector<int> excluded_idx;

    bool operator>(const State& other) const { return weight > other.weight; }
};

int N, M, K;
vector<Edge> all_edges;

pair<long long, vector<int>> get_mst(const vector<int>& forced, const vector<int>& excluded) {
    DSU dsu(N);
    long long total_w = 0;
    vector<int> edges_in_mst;
    set<int> excl_set(excluded.begin(), excluded.end());
    int components = N;

    for (int idx : forced) {
        if (dsu.unite(all_edges[idx].u, all_edges[idx].v)) {
            total_w += all_edges[idx].w;
            edges_in_mst.push_back(idx);
            components--;
        } else return {-1, {}}; // Ràng buộc mâu thuẫn (tạo chu trình)
    }

    for (int i = 0; i < M; ++i) {
        if (excl_set.count(i)) continue;
        bool already_forced = false;
        for(int f : forced) if(f == i) already_forced = true;
        if(already_forced) continue;

        if (dsu.unite(all_edges[i].u, all_edges[i].v)) {
            total_w += all_edges[i].w;
            edges_in_mst.push_back(i);
            components--;
        }
    }

    if (components != 1) return {-1, {}}; // Không liên thông
    sort(edges_in_mst.begin(), edges_in_mst.end());
    return {total_w, edges_in_mst};
}

int main() {
    cin >> N >> M >> K;
    for (int i = 0; i < M; ++i) {
        int u, v, c; cin >> u >> v >> c;
        all_edges.push_back({u, v, c, i});
    }
    sort(all_edges.begin(), all_edges.end());

    priority_queue<State, vector<State>, greater<State>> pq;
    auto initial = get_mst({}, {});
    if (initial.first != -1) {
        pq.push({initial.first, initial.second, {}, {}});
    }

    long long result = -1;
    for (int i = 1; i <= K; ++i) {
        if (pq.empty()) break;
        State current = pq.top(); pq.pop();
        if (i == K) { result = current.weight; break; }

        vector<int> current_forced = current.forced_idx;
        for (int j = 0; j < current.mst_edges_idx.size(); ++j) {
            int edge_to_exclude = current.mst_edges_idx[j];
            
            // Chỉ xét các cạnh không nằm trong tập forced ban đầu của State này
            bool is_already_forced = false;
            for(int f : current.forced_idx) if(f == edge_to_exclude) is_already_forced = true;
            if (is_already_forced) continue;

            vector<int> next_excluded = current.excluded_idx;
            next_excluded.push_back(edge_to_exclude);
            
            auto next_mst = get_mst(current_forced, next_excluded);
            if (next_mst.first != -1) {
                pq.push({next_mst.first, next_mst.second, current_forced, next_excluded});
            }
            current_forced.push_back(edge_to_exclude);
        }
    }

    cout << result << endl;
    return 0;
}