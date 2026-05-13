// Time:O(MlogM+K⋅N⋅MlogN)
// Space:O(K⋅N+M)


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

/*
==================================================
EDGE
==================================================

u-v : cạnh
w   : trọng số
id  : số thứ tự cạnh
*/
struct Edge {

    int u, v, w, id;

    /*
    dùng để sort cạnh tăng dần theo weight
    */
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

/*
==================================================
DSU (DISJOINT SET UNION)
==================================================

Dùng cho Kruskal
*/
struct DSU {

    /*
    parent[i]
    = cha của i
    */
    vector<int> parent;

    /*
    ban đầu mỗi đỉnh là cha của chính nó
    */
    DSU(int n) {

        parent.resize(n + 1);

        for(int i=1; i<=n; ++i)
            parent[i] = i;
    }

    /*
    tìm root của tập hợp

    có path compression
    */
    int find(int i) {

        /*
        nếu là root
        */
        if(parent[i] == i)
            return i;

        /*
        nén đường đi
        */
        return parent[i] = find(parent[i]);
    }

    /*
    nối 2 tập hợp
    */
    bool unite(int i, int j) {

        int root_i = find(i);
        int root_j = find(j);

        /*
        nếu khác component
        thì nối lại
        */
        if (root_i != root_j) {

            parent[root_i] = root_j;

            return true;
        }

        /*
        nếu cùng root

        => tạo chu trình
        */
        return false;
    }
};

/*
==================================================
STATE
==================================================

Lưu 1 trạng thái MST
*/
struct State {

    /*
    tổng trọng số MST
    */
    long long weight;

    /*
    danh sách cạnh trong MST
    */
    vector<int> mst_edges_idx;

    /*
    các cạnh BẮT BUỘC phải có
    */
    vector<int> forced_idx;

    /*
    các cạnh BỊ CẤM dùng
    */
    vector<int> excluded_idx;

    /*
    priority_queue min heap
    */
    bool operator>(const State& other) const {

        return weight > other.weight;
    }
};

int N, M, K;

/*
toàn bộ cạnh
*/
vector<Edge> all_edges;

/*
==================================================
GET MST
==================================================

Tạo MST với:

forced   : cạnh bắt buộc phải lấy
excluded : cạnh cấm lấy
*/
pair<long long, vector<int>>
get_mst(
    const vector<int>& forced,
    const vector<int>& excluded
) {

    /*
    DSU cho Kruskal
    */
    DSU dsu(N);

    /*
    tổng trọng số MST
    */
    long long total_w = 0;

    /*
    các cạnh được chọn vào MST
    */
    vector<int> edges_in_mst;

    /*
    set để check excluded nhanh
    */
    set<int> excl_set(excluded.begin(), excluded.end());

    /*
    ban đầu có N component
    */
    int components = N;

    /*
    ==================================================
    BƯỚC 1:
    THÊM FORCED EDGES
    ==================================================
    */

    for (int idx : forced) {

        /*
        thử nối cạnh forced
        */
        if (
            dsu.unite(
                all_edges[idx].u,
                all_edges[idx].v
            )
        ) {

            /*
            nối thành công
            */

            total_w += all_edges[idx].w;

            edges_in_mst.push_back(idx);

            components--;
        }

        /*
        nếu unite fail

        => forced edges tạo chu trình

        => MST không hợp lệ
        */
        else {

            return {-1, {}};
        }
    }

    /*
    ==================================================
    BƯỚC 2:
    KRUSKAL BÌNH THƯỜNG
    ==================================================
    */

    for (int i = 0; i < M; ++i) {

        /*
        nếu cạnh bị cấm
        */
        if (excl_set.count(i))
            continue;

        /*
        check cạnh này đã forced chưa
        */
        bool already_forced = false;

        for(int f : forced)

            if(f == i)
                already_forced = true;

        /*
        nếu đã forced
        thì bỏ qua
        */
        if(already_forced)
            continue;

        /*
        thử nối cạnh
        */
        if (
            dsu.unite(
                all_edges[i].u,
                all_edges[i].v
            )
        ) {

            /*
            thêm vào MST
            */

            total_w += all_edges[i].w;

            edges_in_mst.push_back(i);

            components--;
        }
    }

    /*
    nếu chưa thành 1 component

    => đồ thị không liên thông
    */
    if (components != 1)
        return {-1, {}};

    /*
    sort để dễ so sánh
    */
    sort(edges_in_mst.begin(), edges_in_mst.end());

    return {total_w, edges_in_mst};
}

int main() {

    cin >> N >> M >> K;

    /*
    nhập cạnh
    */
    for (int i = 0; i < M; ++i) {

        int u, v, c;

        cin >> u >> v >> c;

        all_edges.push_back({u, v, c, i});
    }

    /*
    sort cạnh tăng dần

    cho Kruskal
    */
    sort(all_edges.begin(), all_edges.end());

    /*
    ==================================================
    PRIORITY QUEUE
    ==================================================

    luôn lấy MST nhỏ nhất hiện tại
    */
    priority_queue<
        State,
        vector<State>,
        greater<State>
    > pq;

    /*
    ==================================================
    MST ĐẦU TIÊN
    ==================================================
    */

    auto initial = get_mst({}, {});

    /*
    nếu tồn tại MST
    */
    if (initial.first != -1) {

        /*
        push vào pq

        forced = {}
        excluded = {}
        */
        pq.push({
            initial.first,
            initial.second,
            {},
            {}
        });
    }

    /*
    kết quả MST thứ K
    */
    long long result = -1;

    /*
    ==================================================
    SINH MST THỨ 2,3,4...
    ==================================================
    */

    for (int i = 1; i <= K; ++i) {

        /*
        nếu hết MST
        */
        if (pq.empty())
            break;

        /*
        lấy MST nhỏ nhất hiện tại
        */
        State current = pq.top();

        pq.pop();

        /*
        nếu đây là MST thứ K
        */
        if (i == K) {

            result = current.weight;

            break;
        }

        /*
        current_forced
        sẽ tăng dần
        */
        vector<int> current_forced =
            current.forced_idx;

        /*
        duyệt từng cạnh của MST hiện tại
        */
        for (
            int j = 0;
            j < current.mst_edges_idx.size();
            ++j
        ) {

            /*
            cạnh sẽ bị cấm
            */
            int edge_to_exclude =
                current.mst_edges_idx[j];

            /*
            check cạnh này
            có đang forced không
            */
            bool is_already_forced = false;

            for(int f : current.forced_idx)

                if(f == edge_to_exclude)
                    is_already_forced = true;

            /*
            forced rồi thì không được exclude
            */
            if (is_already_forced)
                continue;

            /*
            tạo excluded mới
            */
            vector<int> next_excluded =
                current.excluded_idx;

            next_excluded.push_back(
                edge_to_exclude
            );

            /*
            tìm MST mới
            */
            auto next_mst =
                get_mst(
                    current_forced,
                    next_excluded
                );

            /*
            nếu tồn tại
            */
            if (next_mst.first != -1) {

                pq.push({
                    next_mst.first,
                    next_mst.second,
                    current_forced,
                    next_excluded
                });
            }

            /*
            thêm cạnh này vào forced

            để các lần sau:
            bắt buộc phải lấy nó
            */
            current_forced.push_back(
                edge_to_exclude
            );
        }
    }

    /*
    in MST thứ K
    */
    cout << result << endl;

    return 0;
}