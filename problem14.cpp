#include <iostream>
#include <vector>

using namespace std;

// Tạm dùng long long thay cho __int128
// (Có thể bị overflow nếu tọa độ quá lớn)
using int128 = long long;

struct Point {
    long long x, y;
};

// Hàm trị tuyệt đối cho long long
int128 abs128(int128 x) {
    return x < 0 ? -x : x;
}

int main() {

    int n;

    if (!(cin >> n))
        return 0;

    // Đỉnh đánh số từ 1 -> n
    vector<Point> p(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
    }

    // =========================
    // cross(i,j)
    // =
    // xi*yj - xj*yi
    //
    // Chính là:
    // 2 * signed area tam giác
    // O - Pi - Pj
    // =========================
    auto cross = [&](int i, int j) -> int128 {

        return
            p[i].x * p[j].y
          - p[j].x * p[i].y;
    };

    // =========================
    // total_s
    // =
    // 2 * diện tích polygon
    // theo công thức Shoelace
    // =========================
    int128 total_s = 0;

    // pref[i]
    // =
    // tổng cross từ cạnh 1 -> i
    vector<int128> pref(n + 1, 0);

    for (int i = 1; i <= n; ++i) {

        int next = (i % n) + 1;

        int128 cp = cross(i, next);

        pref[i] = pref[i - 1] + cp;

        total_s += cp;
    }

    total_s = abs128(total_s);

    // =========================
    // Tìm đường chéo tốt nhất
    // =========================
    int128 min_diff = total_s;

    int best_u = -1;
    int best_v = -1;

    // =========================
    // Duyệt mọi đường chéo (u,v)
    // =========================
    for (int u = 1; u <= n; ++u) {

        for (int v = u + 2; v <= n; ++v) {

            // Bỏ cạnh polygon
            if (u == 1 && v == n)
                continue;

            // =========================
            // Tính:
            // diện tích phần polygon từ u -> v
            //
            // Dùng prefix sum Shoelace
            // =========================
            int128 s_part =
                abs128(
                    (pref[v - 1] - pref[u - 1])
                    + cross(v, u)
                );

            // =========================
            // diff
            // =
            // |Area1 - Area2|
            //
            // Vì:
            // Area2 = Total - Area1
            //
            // =>
            // |A1-A2|
            // =
            // |2*A1-Total|
            // =========================
            int128 diff =
                abs128(
                    2 * s_part - total_s
                );

            // Cập nhật đáp án
            if (diff < min_diff) {

                min_diff = diff;

                best_u = u;
                best_v = v;
            }
        }
    }

    // Output
    cout << best_u << " " << best_v << endl;

    return 0;
}