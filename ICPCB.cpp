#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e3 + 5;
int n, m, p, q;
int a[N][N], dp[N][N];
int maxVal, minVal, pos, L;

int sum(int i, int j, int k, int l) {
  return dp[k][l] - dp[i - 1][l] - dp[k][j - 1] + dp[i - 1][j - 1];
}

signed main() {
  cin >> n >> m >> q >> p;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1] + a[i][j] - dp[i - 1][j - 1];
    }
  }

  while (q--) {
    cin >> L >> pos >> maxVal;
    int A[N], pref[N];

    memset(A, 0, sizeof(A));
    memset(pref, 0, sizeof(pref));

    for (int j = pos; j < pos + L; j++) {
      A[j - pos + 1] = (a[pos][j] * sum(pos - L + 1, j - L + 1, pos, j));
      pref[j - pos + 1] = pref[j - pos] + A[j - pos + 1];
    }

    int res = 0;

    cout << res << '\n';
  }

  while (p--) {
    cin >> L >> pos >> minVal >> maxVal;
  }
}