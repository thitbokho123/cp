#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int LOG = 10;

struct Edge {
    int v, w;
};

vector<Edge> g[N];
int n, h[N], up[N][LOG];

void dfs(int u) {
    for (auto &e : g[u]) {
        int v = e.v;
        if (v == up[u][0]) continue;

        h[v] = h[u] + 1;
        up[v][0] = u;
        for (int j = 1; j < LOG; j++)
            up[v][j] = up[ up[v][j-1] ][j-1];

        dfs(v);
    }
}

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u, v);

    int k = h[u] - h[v];
    for (int j = 0; j < LOG; j++)
        if (k & (1 << j))
            u = up[u][j];

    if (u == v) return u;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int c = 1; c <= t; c++) {
        cin >> n;

        for (int i = 1; i <= n; i++) {
            g[i].clear();
            h[i] = 0;
            for (int j = 0; j < LOG; j++)
                up[i][j] = 0;
        }

        for (int i = 1; i <= n; i++) {
            int x; cin >> x;
            while (x--) {
                int y; cin >> y;
                g[i].push_back({y, 1});
                g[y].push_back({i, 1});
            }
        }

        for (int i = 1; i <= n; i++) {
            if (!h[i]) {
                h[i] = 1;
                dfs(i);
            }
        }

        int q; cin >> q;
        cout << "Case " << c << ": \n";
        while (q--) {
            int u, v;
            cin >> u >> v;
            cout << lca(u, v) << '\n';
        }
    }
}
