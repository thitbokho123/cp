#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  int a[n + 1], b[n + 1], x[n + 1];
  map<int, int> pos;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    x[i] = 0;
    pos[a[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  priority_queue<pair<int, int>> pq;
  int sum = 0, cnt = 0;
  for (int i = 1; i <= n; i++) {
    sum += a[i];
    if (sum >= b[i]) {
      sum -= b[i];
      cnt++;
      x[i] = 1;
      pq.push({b[i], i});
    } else if (!pq.empty() && pq.top().first > b[i]) {
      sum += pq.top().first - b[i];
      x[pq.top().second] = 0;
      x[i] = 1;
      pq.pop();
      pq.push({b[i], i});
    }
  }
  cout << cnt << '\n';
  for (int i = 1; i <= n; i++) {
    if (x[i]) {
      cout << i << ' ';
    }
  }
}