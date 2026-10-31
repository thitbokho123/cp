#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    vector<int> phi(5e12+1);
    vector<int> primes;
    vector<char> is_composite(5e12+1, false);
    phi[0] = 0;

    phi[1] = 1;
    for (int i = 2; i <= 5e12; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            long long x = 1LL * i * p;
            if (x > 5e12) break;
            is_composite[x] = true;
            if (i % p == 0) {
                phi[x] = phi[i] * p;
                break;
            } else {
                phi[x] = phi[i] * (p - 1);
            }
        }
    }

    int a, b;
    cin >> a >> b;
    int ans = 0;
    for (int i = a; i <= a * b; i += a) {
        ans += phi[i];
        ans %= mod;
    }
    cout << ans;
    return 0;
}
