#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int LOG = 10;
int h[N], par[N][LOG], l[N];
int n, q;

struct Edge {
    int v, w;
};

vector<pair<int, int>> g[N];

void dfs(int u) {
    for (auto v : g[u]) {
        if (par[u][0] == v.first) continue;
        h[v.first] = h[u] + 1;
        par[v.first][0] = u;
        l[v.first] = l[u] + v.second;
        for (int i = 1; i < LOG; i++) {
            par[v.first][i] = par[par[v.first][i - 1]][i - 1];
        }
        dfs(v.first);
    }
}

int LCA(int a, int b) {
    if (h[a] < h[b]) swap(a, b);
    int k = h[a] - h[b];
    for (int i = LOG; i >= 0; i--) {
        if ((k >> i) & 1) {
            a = par[a][i];
        }
    }
    if (a == b) return a;
    for (int i = LOG; i >= 0; i--) {
        if (par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int a, b, l;
        cin >> a >> b >> l;
        g[a].push_back({b, l});
        g[b].push_back({a, l});
    }
    dfs(1);
    while (q--) {
        int a, b;
        cin >> a >> b;
        int x = LCA(a, b);
        cout << l[a] + l[b] - 2 * l[x] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}