#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int LOG = 17;
vector<int> g[N];
int par[N][LOG], h[N], n;
int child[N];


// par[i][j] = par[par[i][j-1]][j-1]
void dfs(int u) {
    for (int v : g[u]) {
        if (v == par[u][0]) continue;
        h[v] = h[u] + 1;
        par[v][0] = u;
        for (int j = 1; j < LOG; j++) {
            par[v][j] = par[par[v][j - 1]][j - 1];
        }
        dfs(v);
        child[u] += child[v];
    }
}

int LCA (int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    int k = h[u] - h[v];
    for (int j = 0; j < LOG; j++) {
        if ((k >> j) & 1)  {
            u = par[u][j];
        }
    }
    if (u == v) {
        return u;
    }
    for (int j = LOG - 1; j >= 0; j--) {
        if (par[u][j] != par[v][j]) {
            u = par[u][j];
            v = par[v][j];
        }
    }
    return par[u][0];
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        child[i] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    dfs(1);
    int m;
    cin >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        if (h[a] < h[b]) {
            swap(a, b);
        }
        int u = LCA(a, b);
        int d = h[a] + h[b] - 2 * h[u];
        if (d % 2 == 1) {
            cout << 0;
        } else {
            int k = d / 2;
            int x = a;
            int mid = a;
            for (int j = 0; j < LOG; j++) {
                if ((k >> j) & 1) {
                    mid = par[mid][j];
                }
            }
            for (int j = 0; j < LOG; j++) {
                if (((k - 1) >> j) & 1) {
                    x = par[x][j];
                }
            }
            if (h[a] == h[b]) {
                int y = b;
                for (int j = 0; j < LOG; j++) {
                    if (((k - 1) >> j) & 1) {
                        y = par[y][j];
                    }
                }
                cout << n - child[x] - child[y];
            } else {
                cout << child[mid] - child[x];
            }
        }
        cout << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    solve();
}