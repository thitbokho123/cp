#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 200005;
int n, h[MAXN], dp[MAXN];
int st[4 * MAXN];
int L[MAXN], R[MAXN];

void update(int id, int l, int r, int pos, int val) {
  if (l == r) {
    st[id] = val;
    return;
  }
  int mid = l + ((r - l) >> 1);
  if (pos <= mid) {
    update(id * 2, l, mid, pos, val);
  } else {
    update(id * 2 + 1, mid + 1, r, pos, val);
  }
  st[id] = max(st[id * 2], st[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
  if (l > v || r < u || u > v) {
    return 0;
  }
  if (l >= u && r <= v) {
    return st[id];
  }
  int mid = l + ((r - l) >> 1);
  return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
  }
  vector<int> stack_L, stack_R;
  vector<pair<int, int>> mountains;

  for (int i = 1; i <= n; i++) {
    while (!stack_L.empty() && h[stack_L.back()] < h[i]) {
      stack_L.pop_back();
    }
    L[i] = stack_L.empty() ? 0 : stack_L.back();
    stack_L.push_back(i);
  }

  for (int i = n; i >= 1; i--) {
    while (!stack_R.empty() && h[stack_R.back()] < h[i]) {
      stack_R.pop_back();
    }
    R[i] = stack_R.empty() ? n + 1 : stack_R.back();
    stack_R.push_back(i);
  }

  for (int i = 1; i <= n; i++) {
    mountains.push_back({h[i], i});
  }

  sort(mountains.begin(), mountains.end());
  int ans = 0;

  for (int i = 0; i < n;) {
    int j = i;
    while (j < n && mountains[j].first == mountains[i].first) {
      j++;
    }
    for (int k = i; k < j; k++) {
      int idx = mountains[k].second;
      int max_left = get(1, 1, n, L[idx] + 1, idx - 1);
      int max_right = get(1, 1, n, idx + 1, R[idx] - 1);
      dp[idx] = max(max_left, max_right) + 1;
      ans = max(ans, dp[idx]);
    }
    for (int k = i; k < j; k++) {
      int idx = mountains[k].second;
      update(1, 1, n, idx, dp[idx]);
    }
    i = j;
  }

  cout << ans;
}