#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    int n;
    cin >> n;
    int a[2 * n], b[n];
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for(int j = 0; j < n; j++) {
        cin >> b[j];
    }
    int c[2 * n], d[n];
    for(int i = 0; i < 2 * n - 2; i++) {
        c[i] = a[i] ^ a[i + 1];
    }
    for (int j = 0; j < n - 1; j++) {
        d[j] = b[j] ^ b[j + 1];
    }
    int e[3 * n];
    for (int j = 0; j < n - 1; j++) {
        e[j] = d[j];
    }
    e[n - 1] = -1;
    for (int i = 0; i < 2 * n - 2; i++) {
        e[i + n] = c[i];
    }
    int l = 0, r = 0;
    int z[3 * n];
    fill(z, z + 3 * n, 0);
    for (int i = 1; i < 3 * n - 2; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < 3 * n - 2 && e[z[i]] == e[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for (int i = 0; i < 3 * n - 2; i++) {
        if (z[i] == n - 1) {
            cout << (i - n) % n << ' ' << (b[0] ^ a[i - n]) << '\n';
        }
    }
}