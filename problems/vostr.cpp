#include <bits/stdc++.h>
using namespace std;

#define int long long

int base = 59;
int mod = 1e9 + 7;
int POW[1000007], aHash[1000007], bHash[1000007];

int getAHash(int i, int j) {
    return (((aHash[j] - aHash[i - 1] * POW[j - i + 1])) + mod * mod) % mod;
}

int getBHash(int i, int j) {
    return (((bHash[j] - bHash[i - 1] * POW[j - i + 1])) + mod * mod) % mod;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int la, lb;
    cin >> la >> lb;
    string a, b;
    cin >> a >> b;
    POW[0] = 1;
    for (int i = 1; i <= max(la, lb); i++) {
        POW[i] = (POW[i - 1] * base) % mod;
    }

    a = " " + a;
    b = " " + b;

    for (int i = 1; i <= la; i++) {
        aHash[i] = ((aHash[i - 1] * base) % mod + a[i] - 'a' + 1) % mod;
    }

    for (int i = 1; i <= lb; i++) {
        bHash[i] = ((bHash[i - 1] * base) % mod + b[i] - 'a' + 1) % mod;
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r, u ,v;
        cin >> l >> r >> u >> v;
        if (getAHash(l, r) == getBHash(u, v)) {
            cout << "=";
        } else if (getAHash(l, r) < getBHash(u, v)) {
            cout << "<";
        } else {
            cout << ">";
        }
    }
}