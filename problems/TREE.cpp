#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, q;
vector<int> g[200001];
int depth[200001];
int up[200001][20];

void dfs(int u, int p = 0) {
  up[u][0] = p;
  for (auto v : g[u]) {
    if (v != p) {
      depth[v] = depth[u] + 1;
      dfs(v, u);
    }
  }
}

void binlift() {
  for (int j = 1; j < 20; j++) {
    for (int i = 1; i <= n; i++) {
      up[i][j] = up[up[i][j - 1]][j - 1];
    }
  }
}

int lca(int u, int v) {
  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  for (int j = 19; j >= 0; j--) {
    if ((depth[v] - (1 << j)) >= depth[u]) {
      v = up[v][j];
    }
  }
  if (u == v) return u;
  for (int j = 19; j >= 0; j--) {
    if (up[u][j] != up[v][j]) {
      u = up[u][j];
      v = up[v][j];
    }
  }
  return up[u][0];
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  depth[1] = 1;
  dfs(1);
  binlift();
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << depth[a] + depth[b] - 2 * depth[lca(a, b)] << '\n';
  }
}