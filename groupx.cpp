#include <bits/stdc++.h>
using namespace std;

#define int long long
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  int q[n][n] = {}, s[n] = {}, sum[n] = {}, ans[n] = {};

  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    q[u][v] = q[v][u] = w;
  }

  int mx = -1;

  mt19937 rng(1337);
  auto start_time = chrono::steady_clock::now();
  double time_limit = 1.93;

  int iter_count = 0;

  int cur = 0;
  for (int i = 0; i < n; i++) {
    s[i] = rng() % 2;
    sum[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    if (s[i] == 1) {
      cur += q[i][i];
      for (int j = i + 1; j < n; j++) {
        if (s[j] == 1) {
          cur += 2 * q[i][j];
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[j] == 1) {
        sum[i] += q[i][j];
      }
    }
  }

  if (cur > mx) {
    mx = cur;
    for (int i = 0; i < n; i++) {
      ans[i] = s[i];
    }
  }

  while (true) {
    if ((++iter_count & 63) == 0) {
      auto now = chrono::steady_clock::now();
      if (chrono::duration<double>(now - start_time).count() > time_limit)
        break;
    }

    int num_flips = rng() % 10 + 2;
    for (int step = 0; step < num_flips; step++) {
      int k = rng() % n;
      int diff = 0;

      if (s[k] == 0) {
        diff = 2 * sum[k] + q[k][k];
      } else {
        diff = -(2 * (sum[k] - q[k][k]) + q[k][k]);
      }

      cur += diff;
      if (s[k] == 0) {
        s[k] = 1;
        for (int i = 0; i < n; i++) {
          sum[i] += q[i][k];
        }
      } else {
        s[k] = 0;
        for (int i = 0; i < n; i++) {
          sum[i] -= q[i][k];
        }
      }
    }

    bool flag = true;
    while (flag) {
      flag = false;

      vector<int> p(n);
      iota(p.begin(), p.end(), 0);
      shuffle(p.begin(), p.end(), rng);

      for (int k : p) {
        int diff = 0;
        if (s[k] == 0) {
          diff = 2 * sum[k] + q[k][k];
        } else {
          diff = -(2 * (sum[k] - q[k][k]) + q[k][k]);
        }

        if (diff > 0) {
          cur += diff;
          flag = true;

          if (s[k] == 0) {
            s[k] = 1;
            for (int i = 0; i < n; i++) {
              sum[i] += q[i][k];
            }
          } else {
            s[k] = 0;
            for (int i = 0; i < n; i++) {
              sum[i] -= q[i][k];
            }
          }
        }
      }
    }

    if (cur > mx) {
      mx = cur;
      for (int i = 0; i < n; i++) {
        ans[i] = s[i];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }
}