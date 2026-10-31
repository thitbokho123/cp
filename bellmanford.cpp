#include <bits/stdc++.h>
using namespace std;

const long long INF =
    1e18;  // Dùng 1e18 an toàn để tránh underflow/overflow khi cộng trừ

struct Edge {
  int u, v;
  long long w;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  if (!(cin >> n >> m)) return 0;

  vector<Edge> e;
  // Đọc input: giữ NGUYÊN trọng số, tìm đường dài nhất luôn cho đỡ rối
  for (int i = 0; i < m; i++) {
    int u, v;
    long long w;
    cin >> u >> v >> w;
    e.push_back({u, v, w});  // Chỉ push 1 chiều
  }

  vector<long long> D(n + 1,
                      -INF);  // Khởi tạo -INF cho bài toán tìm đường DÀI NHẤT
  D[1] = 0;

  // Chạy Bellman-Ford n-1 lần
  for (int T = 1; T < n; T++) {
    for (auto E : e) {
      if (D[E.u] != -INF && D[E.v] < D[E.u] + E.w) {
        D[E.v] = D[E.u] + E.w;
      }
    }
  }

  // Vòng lặp n và DFS/BFS để kiểm tra chu trình dương đi đến đích
  // Bước 1: Gom các đỉnh vẫn còn tăng điểm được
  vector<int> changed;
  for (auto E : e) {
    if (D[E.u] != -INF && D[E.v] < D[E.u] + E.w) {
      changed.push_back(E.v);
      D[E.v] = D[E.u] + E.w;  // Cập nhật luôn
    }
  }

  // Bước 2: Xem các đỉnh chu trình này có với tới được đỉnh n không
  vector<bool> in_cycle_path(n + 1, false);
  if (!changed.empty()) {
    // Dựng danh sách kề để lan truyền BFS
    vector<vector<int>> adj(n + 1);
    for (auto E : e) {
      adj[E.u].push_back(E.v);
    }

    queue<int> q;
    for (int u : changed) {
      q.push(u);
      in_cycle_path[u] = true;
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : adj[u]) {
        if (!in_cycle_path[v]) {
          in_cycle_path[v] = true;
          q.push(v);
        }
      }
    }
  }

  // Bước 3: Xuất kết quả
  if (in_cycle_path[n]) {
    cout << -1 << "\n";
  } else {
    cout << D[n] << "\n";
  }

  return 0;
}