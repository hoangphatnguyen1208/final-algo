#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;

bool isPrime[MAXN];
int n;

void sieve() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i < 2*n; i++) {
        if (isPrime[i]) {
            for (int j = i*i; j < 2*n; j += i) {
                isPrime[j] = 0;
            }
        }
    }
}

int main() {
    cin >> n;
    sieve();

    vector <int> prime;
    for (int i = 2; i < 2*n; i++) {
        if (isPrime[i]) prime.push_back(i);
    }

    int ans = 0;
    for (int i = 0; i < prime.size(); i++) {
        for (int j = 0; j <= i; j++) {
            if (prime[i] + prime[j] <= 2*n) {
                if ((prime[i]+prime[j]) % 2 == 0) ans++;
            }
            else {
                break;
            }
        }
    }
    cout << ans;
    return 0;
}