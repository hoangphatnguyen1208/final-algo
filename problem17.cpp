// Thời gian: O(2^L ⋅ L) với L=9
// Không gian: O(1)

#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    int n;
    // Đọc số nguyên dương n từ đầu vào
    if (!(cin >> n)) return 0;

    // Duyệt qua tất cả 511 khả năng của số m (2^9 - 1)
    for (int k = 1; k < (1 << 9); ++k) {
        ll m = 0;
        ll p10 = 1; // Lũy thừa của 10 để xây dựng số thập phân
        int temp_k = k;

        // Chuyển đổi các bit của k thành các chữ số 0, 1 của m
        while (temp_k > 0) {
            if (temp_k & 1) {
                m += p10;
            }
            p10 *= 10;
            temp_k >>= 1;
        }

        // Kiểm tra điều kiện chia hết
        if (m % n == 0) {
            cout << m << endl;
            return 0; // Tìm thấy số nhỏ nhất nên thoát luôn
        }
    }

    return 0;
}