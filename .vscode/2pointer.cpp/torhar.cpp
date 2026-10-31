#include <bits/stdc++.h>
using namespace std;

long long x, y;

long long f(long long t) {
    return (long long)((t % y) * 10);
}

signed main() {
    cin >> x >> y;

    long long tortoise = f(x), hare = f(x);
    while (true) {
        tortoise = f(tortoise);
        hare = f(f(hare));
        if (tortoise == hare) {
            break;
        }
    }

    long long mu = 0, p = f(x);
    while (p != tortoise) {
        p = f(p);
        tortoise = f(tortoise);
        mu++;
    }

    long long lambda = 0;
    while (true) {
        lambda++;
        p = f(p);
        if (tortoise == p) {
            break;
        }
    }

    long long cnt = 0;
    long long t = mu + lambda;

    cout << x / y;

    while (t--) {
        if (cnt == 0) cout << '.';
        if (cnt == mu) cout << '(';
        cout << f(x) / y;
        
        cnt++;
        x = f(x);
    }
    cout << ')';
}