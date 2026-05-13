#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double x1, y1, x2, y2, R;
    // Đọc dữ liệu đầu vào
    if (!(cin >> x1 >> y1 >> x2 >> y2 >> R)) return 0;

    // Tính khoảng cách d giữa hai tâm
    double d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    double d = sqrt(d2);
    double PI = acos(-1.0);
    double areaUnion;

    if (d >= 2 * R) {
        // Trường hợp không giao nhau
        areaUnion = 2 * PI * R * R;
    } else if (d == 0) {
        // Trường hợp trùng nhau hoàn toàn
        areaUnion = PI * R * R;
    } else {
        // Trường hợp giao nhau: Tính diện tích phần giao (areaInt)
        // areaInt = 2 * (diện tích quạt - diện tích tam giác cân)
        double alpha = 2 * acos(d / (2 * R));
        double areaInt = R * R * (alpha - sin(alpha));
        areaUnion = 2 * PI * R * R - areaInt;
    }

    // In kết quả với chính xác 3 chữ số thập phân
    cout << fixed << setprecision(3) << areaUnion << endl;

    return 0;
}