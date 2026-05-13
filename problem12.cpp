#include <iostream>
#include <cmath>

using namespace std;

void solve() {
    int S;
    if (!(cin >> S)) return;

    for (int a = 0; a * a <= S; ++a) {
        int b2 = S - a * a;
        int b = sqrt(b2);
        if (b * b == b2) {
            // Đã tìm thấy a và b thỏa mãn a^2 + b^2 = S
            // Xuất 4 đỉnh (bắt đầu từ 0, 0 cho đơn giản)
            cout << "0 0" << endl;
            cout << a << " " << b << endl;
            cout << a - b << " " << b + a << endl;
            cout << -b << " " << a << endl;
            return;
        }
    }

    cout << "Impossible" << endl;
}

int main() {
    solve();
    return 0;
}