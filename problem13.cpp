#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
    int id;
};

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    vector<Point> p(n);
    int startIdx = 0;
    
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].id = i + 1; // Lưu lại chỉ số 1-based
        // Tìm điểm cực trái (min x, sau đó min y)
        if (p[i].x < p[startIdx].x || (p[i].x == p[startIdx].x && p[i].y < p[startIdx].y)) {
            startIdx = i;
        }
    }
    
    Point origin = p[startIdx];
    vector<pair<double, int>> others;
    
    for (int i = 0; i < n; ++i) {
        if (i == startIdx) continue;
        // Tính góc cực của mỗi điểm so với điểm gốc
        double angle = atan2((double)p[i].y - origin.y, (double)p[i].x - origin.x);
        others.push_back({angle, p[i].id});
    }
    
    // Sắp xếp theo góc tăng dần
    sort(others.begin(), others.end());
    
    // Chọn điểm ở vị trí trung tâm trong danh sách n-1 điểm
    // Index n/2 - 1 sẽ là phần tử thứ n/2
    int secondPointId = others[n / 2 - 1].second;
    
    cout << origin.id << " " << secondPointId << endl;
    
    return 0;
}