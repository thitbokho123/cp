#include <bits/stdc++.h>
using namespace std;

struct element {
  int a, b, c;
};

bool cmp(element x, element y) { return x.b < y.b; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  element e[n + 1];
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].b >> e[i].c;
  }
  map<int, long long> dp;
  dp[0] = 0;
  sort(e + 1, e + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    auto it = dp.lower_bound(e[i].a);
    it--;
    long long cur = it->second + e[i].c;
    if (cur > dp.rbegin()->second) {
      dp[e[i].b] = cur;
    }
  }
  cout << dp.rbegin()->second;
}