#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAX_N = 50005;
const int MAX_TRIE_NODES = 1000005;

int a[MAX_N];
vector<int> candidates;

struct Trie {
  struct Node {
    int child[2];
    int exist, cnt;
  } nodes[MAX_TRIE_NODES];

  int cur;
  Trie() : cur(0) {
    memset(nodes[0].child, -1, sizeof(nodes[0].child));
    nodes[0].exist = nodes[0].cnt = 0;
  }

  int newnode() {
    cur++;
    memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
    nodes[cur].exist = nodes[cur].cnt = 0;
    return cur;
  }

  void add_number(int x) {
    if (x == 0) return;
    int msb = 63 - __builtin_clzll(x);
    int pos = 0;
    for (int i = msb; i >= 0; i--) {
      int c = (x >> i) & 1;
      if (nodes[pos].child[c] == -1) nodes[pos].child[c] = newnode();
      pos = nodes[pos].child[c];
      nodes[pos].cnt++;
    }
    nodes[pos].exist++;
  }

  int get_lcp_value(int n) {
    int pos = 0;
    int lcp_val = 0;

    while (true) {
      int next_node = -1;
      int bit = -1;

      if (nodes[pos].child[0] != -1 && nodes[nodes[pos].child[0]].cnt == n) {
        next_node = nodes[pos].child[0];
        bit = 0;
      } else if (nodes[pos].child[1] != -1 &&
                 nodes[nodes[pos].child[1]].cnt == n) {
        next_node = nodes[pos].child[1];
        bit = 1;
      }

      if (next_node != -1) {
        lcp_val = (lcp_val << 1) | bit;
        pos = next_node;
      } else {
        break;
      }
    }
    return lcp_val;
  }
};

int get_bit_len(int x) {
  if (x == 0) return 0;
  return 64 - __builtin_clzll(x);
}

int get_pair_lcp(int x, int y) {
  if (x == 0 || y == 0) return 0;
  int len_x = get_bit_len(x);
  int len_y = get_bit_len(y);

  while (len_x > len_y) {
    x >>= 1;
    len_x--;
  }
  while (len_y > len_x) {
    y >>= 1;
    len_y--;
  }

  while (x != y) {
    x >>= 1;
    y >>= 1;
  }
  return x;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n;
  if (!(cin >> n)) return 0;

  Trie trie;
  bool all_zero = true;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] > 0) all_zero = false;
    trie.add_number(a[i]);
  }

  if (all_zero) {
    cout << 0 << "\n";
    return 0;
  }

  int x = trie.get_lcp_value(n);

  int cur_pre = x;

  while (true) {
    int t = cur_pre;
    for (int k = 0; k <= 18; k++) {
      candidates.push_back(t);
      t = (t << 1) | 1;
    }
    if (cur_pre == 0) break;
    cur_pre >>= 1;
  }

  int min_cost = 1e18;
  for (int T : candidates) {
    int cur_cost = 0;
    int len_T = get_bit_len(T);

    for (int i = 1; i <= n; i++) {
      int pair_lcp = get_pair_lcp(a[i], T);
      int cost_i = get_bit_len(a[i]) + len_T - 2 * get_bit_len(pair_lcp);
      cur_cost += cost_i;
    }
    min_cost = min(min_cost, cur_cost);
  }
  cout << min_cost << "\n";
  return 0;
}