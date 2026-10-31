#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, q;
int a[200001];
int bit[200001];

void update(int u, int v) {
  while (u <= n) {
    bit[u] += v;
    u += u & (-u);
  }
}

int get(int u, int v) {
  u -= 1;
  int ans_u = 0, ans_v = 0;
  while (u >= 1) {
    ans_u += bit[u];
    u -= u & (-u);
  }
  while (v >= 1) {
    ans_v += bit[v];
    v -= v & (-v);
  }
  return ans_v - ans_u;
}

signed main() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    update(i, a[i]);
  }
  while (q--) {
    int type, y, z;
    cin >> type >> y >> z;
    if (type == 1) {
      update(y, z - a[y]);
      a[y] = z;
    } else {
      cout << get(y, z) << '\n';
    }
  }
}