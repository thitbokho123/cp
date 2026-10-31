#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, s;
  cin >> n >> s;
  int p[n + 1];
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
    p[i] = p[i] - s * i;
  }
  int res = 0;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 1; i <= n; i++) {
    pq.push(p[i]);
    int x = pq.top();
    if (x < p[i]) {
      res += p[i] - x;
      pq.pop();
      pq.push(p[i] - x + x);
    }
  }
  cout << res << '\n';
}