#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  int a[n + 1];
  map<int, int> cnt;
  a[0] = -1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    cnt[a[i]]++;
  }
  sort(a + 1, a + n + 1);
  int difel = a[n];
  int dp[difel + 1][2];
  for (int i = 0; i <= difel; i++) {
    dp[i][0] = dp[i][1] = 0;
  }
  for (int i = 1; i <= difel; i++) {
    dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
    dp[i][1] = dp[i - 1][0] + cnt[i] * i;
  }
  cout << max(dp[difel][0], dp[difel][1]);
}