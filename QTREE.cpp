#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, t;
int sz[N], par[N], chainHead[N], chainId[N], pos[N], arr[N], h[N], st[N * 4], val[N];
int curChain, curPos;

int U[N], V[N], edgeToNode[N];

vector<pair<int, int>> g[N];

void build(int id, int l, int r) {
    if (l == r) {
        st[id] = val[arr[l]];
        return;
    }
    int mid = l + ((r - l) >> 1);
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    st[id] = max(st[id * 2], st[id * 2 + 1]);
}

void update(int id, int l, int r, int pos, int val) {
    if (l > pos || r < pos) {
        return;
    }
    if (l == r && l == pos) {
        st[id] = val;
        return;
    }
    int mid = l + ((r - l) >> 1);
    update(id * 2, l, mid, pos, val);
    update(id * 2 + 1, mid + 1, r, pos, val);
    st[id] = max(st[id * 2], st[id * 2 + 1]);
} 

int calc(int id, int tl, int tr, int l, int r) {
    if (tl > r || tr < l) {
        return -1e9; 
    }
    if (l <= tl && tr <= r) {
        return st[id];
    }
    int mid = tl + ((tr - tl) >> 1);
    return max(calc(id * 2, tl, mid, l, r), calc(id * 2 + 1, mid + 1, tr, l, r));
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

void upd(int x, int val) {
    update(1, 1, n, pos[x], val);
}

int Query(int u, int v) {
    int lca = LCA(u, v);
    int ans = -1e9;
    while (chainId[u] != chainId[lca]) {
        ans = max(ans, calc(1, 1, n, pos[chainHead[chainId[u]]], pos[u]));
        u = par[chainHead[chainId[u]]];
    }
    while (chainId[v] != chainId[lca]) {
        ans = max(ans, calc(1, 1, n, pos[chainHead[chainId[v]]], pos[v]));
        v = par[chainHead[chainId[v]]];
    }
    
    if (u == v) return ans; 
    
    if (h[u] < h[v]) {
        ans = max(ans, calc(1, 1, n, pos[u] + 1, pos[v]));
    } else {
        ans = max(ans, calc(1, 1, n, pos[v] + 1, pos[u]));
    }
    return ans;
}

void dfs(int u) {
    sz[u] = 1;
    for (auto v : g[u]) {
        if (v.first == par[u]) continue;
        par[v.first] = u;
        h[v.first] = h[u] + 1;
        val[v.first] = v.second;
        dfs(v.first);
        sz[u] += sz[v.first];
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
        if (v.first == par[u]) continue;
        if (nxt == 0 || sz[v.first] > sz[nxt]) {
            nxt = v.first;
        }
    }
    if (nxt) {
        hld(nxt);
    }
    for (auto v : g[u]) {
        if (v.first == par[u]) continue;
        if (v.first != nxt) {
            curChain++;
            hld(v.first);
        }
    }
}

void solve() {
    cin >> t;
    while (t--) {
        cin >> n;
        curPos = curChain = 1;
        for (int i = 1; i <= n; i++) {
            g[i].clear();        
            chainHead[i] = 0;    
        }
        for (int i = 1; i < n; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            U[i] = u; V[i] = v; 
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        dfs(1);
        
        for (int i = 1; i < n; i++) {
            if (h[U[i]] > h[V[i]]) edgeToNode[i] = U[i];
            else edgeToNode[i] = V[i];
        }
        
        hld(1);
        build(1, 1, n);
        string type;
        while (cin >> type) {
            if (type == "QUERY") {
                int a, b;
                cin >> a >> b;
                cout << Query(a, b) << '\n';
            } else if (type == "CHANGE") {
                int a, b;
                cin >> a >> b;
                upd(edgeToNode[a], b); 
            } else {
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}