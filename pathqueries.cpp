#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e5 + 5;
int n, q;
int par[N], h[N], sz[N];
vector<int> g[N];
int chainHead[N], curChain, curPos, pos[N];
int chainId[N], arr[N], val[N];

void dfs(int u) {
    sz[u] = 1;
    for (auto v : g[u]) {
        if (v == par[u]) continue;
        h[v] = h[u] + 1;
        par[v] = u;
        dfs(v);
        sz[u] += sz[v]; 
    }
}

void hld(int u) {
    if (!chainHead[curChain]) {
        chainHead[curChain] = u;
    }
    chainId[u] = curChain;
    pos[u] = curPos;
    arr[curPos] = u;
    curPos++;
    int nxt = 0;
    for (auto v : g[u]) {
        if (v == par[u]) continue;
        if (nxt == 0 || sz[v] > sz[nxt]) {
            nxt = v;
        }
    }
    if (nxt) {
        hld(nxt);
    }
    for (auto v : g[u]) {
        if (v == par[u] || v == nxt) continue;
        curChain++;
        hld(v);
    }
}

int LCA(int u, int v) {
    while (chainId[u] != chainId[v]) {
        if (chainId[u] > chainId[v]) {
            u = par[chainHead[chainId[u]]];
        } else {
            v = par[chainHead[chainId[v]]];
        }
    }
    if (h[u] < h[v]) return u;
    return v;
}

int st[4 * N];

void build(int id, int l, int r) {
    if (l == r) {
        st[id] = val[arr[l]];
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

void upd(int id, int l, int r, int pos, int val) {
    if (l > pos || r < pos) {
        return;
    }
    if (l == r && l == pos) {
        st[id] = val;
        return;
    }
    int mid = l + ((r - l) >> 1);
    upd(id * 2, l, mid, pos, val);
    upd(id * 2 + 1, mid + 1, r, pos, val);
    st[id] = st[id * 2] + st[id * 2 + 1];
}

int calc(int id, int l, int r, int u, int v) {
    if (l > v || r < u) {
        return 0;
    }
    if (l >= u && r <= v) {
        return st[id];
    }
    int mid = l + ((r - l) >> 1);
    return calc(id * 2, l, mid, u, v) + calc(id * 2 + 1, mid + 1, r, u, v);
}

void update(int x, int val) {
    upd(1, 1, n, pos[x], val);
}

int query(int u, int v) {
    int lca = LCA(u, v);
    int ans = 0;
    while (chainId[u] != chainId[lca]) {
        ans += calc(1, 1, n, pos[chainHead[chainId[u]]], pos[u]);
        u = par[chainHead[chainId[u]]];
    }
    while (chainId[v] != chainId[lca]) {
        ans += calc(1, 1, n , pos[chainHead[chainId[v]]], pos[v]);
        v = par[chainHead[chainId[v]]];
    }
    if (h[u] < h[v]) {
        ans += calc(1, 1, n, pos[u], pos[v]);
    } else {
        ans += calc(1, 1, n, pos[v], pos[u]);
    }
    return ans;
}

void solve() {
    cin >> n >> q;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        sum += val[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    curPos = curChain = 1;
    dfs(1);
    hld(1);
    build(1, 1, n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x, value;
            cin >> x >> value;
            update(x, value);
        } else {
            int s;
            cin >> s;
            cout << calc(1, 1, n, pos[s], pos[s] + sz[s] - 1) << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}