#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int n;
    // Bước 1: Đọc n từ dòng đầu tiên
    if (!(cin >> n)) return 0;

    // Bước 2: Đọc hoán vị a từ dòng thứ hai
    vector<int> start(n);
    for (int i = 0; i < n; ++i) {
        cin >> start[i];
    }

    // Tạo trạng thái đích (ví dụ: 1 2 3 4 5)
    vector<int> target(n);
    for (int i = 0; i < n; ++i) target[i] = i + 1;

    // Nếu mảng đã sắp xếp sẵn
    if (start == target) {
        cout << 0 << endl;
        return 0;
    }

    // BFS khởi tạo
    queue<vector<int>> q;
    map<vector<int>, int> dist; // Lưu số bước đến mỗi trạng thái

    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        vector<int> curr = q.front();
        int d = dist[curr];
        q.pop();

        // Thử tất cả các phép đảo ngược tiền tố độ dài từ 2 đến n
        for (int len = 2; len <= n; ++len) {
            vector<int> next_state = curr;
            // Đảo ngược tiền tố từ vị trí 0 đến len-1
            reverse(next_state.begin(), next_state.begin() + len);

            // Nếu trạng thái này chưa từng gặp
            if (dist.find(next_state) == dist.end()) {
                // Kiểm tra xem đã là đích chưa
                if (next_state == target) {
                    cout << d + 1 << endl;
                    return 0;
                }
                dist[next_state] = d + 1;
                q.push(next_state);
            }
        }
    }

    return 0;
}