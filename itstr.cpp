#include <bits/stdc++.h>
using namespace std;

const int MOD = 1007050321;
const int N = 1e5 + 5;
int st[4 * N], len[4 * N];
string s;
int m, n;
int pow2[N];

void preprocess() {
    pow2[0] = 1;
    for (int i = 1; i < N; i++) {
        pow2[i] = 2 * pow2[i - 1];
        pow2[i] %= MOD;
    }
}

void build(int id, int l, int r) {
    if (l == r) {
        st[id] = s[l] - 48;
        len[id] = 1;
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    len[id] = len[id * 2] + len[id * 2 + 1];
    st[id] = ((1LL * st[id * 2] * (pow2[len[id * 2 + 1]]) % MOD) % MOD + st[id * 2 + 1]) % MOD;
}

void updateLen(int id, int l, int r, int i) {
    if (l > i || r < i) {
        return;
    }
    if (l == r) {
        len[id] = 0;
        st[id] = 0;
        return;
    }
    int mid = l + ((r - l) >> 1);
    updateLen(id * 2, l, mid, i);
    updateLen(id * 2 + 1, mid + 1, r, i);
    len[id] = len[id * 2] + len[id * 2 + 1];
    st[id] = ((1LL * st[id * 2] * (pow2[len[id * 2 + 1]]) % MOD) % MOD + st[id * 2 + 1]) % MOD;
}

int getLen(int id, int l, int r, int u, int v) {
    if (u > r || v < l) {
        return 0;
    }
    if (u <= l && v >= r) {
        return len[id];
    }
    int mid = l + ((r - l) >> 1);
    return getLen(id * 2, l, mid, u, v) + getLen(id * 2 + 1, mid + 1, r, u, v);
}

int getIndex(int p) {
    int l = 1, r = n - 1;
    int ans = -1;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (getLen(1, 1, n - 1, 1 , mid) >= p) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

pair<long long, int> getNum(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return {0, 0};
    }
    if (u <= l && v >= r) {
        return {st[id], len[id]};
    }
    int mid = l + ((r - l) >> 1);
    pair<long long, int> L = getNum(id * 2, l, mid, u, v);
    pair<long long, int> R = getNum(id * 2 + 1, mid + 1, r, u, v);
    
    long long val = ((1LL * L.first * pow2[R.second]) % MOD + R.first) % MOD;
    int length = L.second + R.second;
    return {val, length};
}

void solve() {
    preprocess();
    cin >> s;
    s = '#' + s;
    n = s.length();
    build(1, 1, n - 1);
    cin >> m;
    while (m--) {
        char type;
        cin >> type;
        if (type == '?') {
            int l, r;
            cin >> l >> r;
            int realL = getIndex(l), realR = getIndex(r);
            cout << getNum(1, 1, n - 1, realL, realR).first << '\n';
        } else {
            int p;
            cin >> p;
            int realP = getIndex(p);
            updateLen(1, 1, n - 1, realP);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}