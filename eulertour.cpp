#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int S = 450;  // Block size cho Mo's Algorithm (Căn bậc hai của 200,000)

vector<int> adj[MAXN];
int n, q;
int a[MAXN];

// Các mảng cho Euler Tour
int st[MAXN], en[MAXN];
int f[MAXN];  // Mảng f lưu trực tiếp giá trị của đỉnh sau khi trải phẳng
int timer = 0;

// Các biến phục vụ Mo's Algorithm
int cnt[MAXN];  // Đếm tần số xuất hiện của các giá trị (đã rời rạc hóa)
int cur_ans = 0;
int ans[MAXN];

struct Query {
  int l, r, id;
};

// Even-Odd Sorting tối ưu hằng số thời gian
bool cmp(const Query& A, const Query& B) {
  if (A.l / S != B.l / S) return A.l < B.l;
  return (A.l / S % 2 == 0) ? A.r < B.r : A.r > B.r;
}

// Euler Tour 1 lần (Trải phẳng cây con thành đoạn liên tiếp)
void dfs(int u, int p) {
  st[u] = ++timer;
  f[timer] = a[u];

  for (auto v : adj[u]) {
    if (v != p) dfs(v, u);
  }

  en[u] = timer;  // Chỉ số cuối cùng kết thúc cây con gốc u
}

// Thêm một phần tử vào cửa sổ Mo
void add(int idx) {
  if (cnt[f[idx]] == 0) cur_ans++;
  cnt[f[idx]]++;
}

// Bớt một phần tử khỏi cửa sổ Mo
void remove(int idx) {
  cnt[f[idx]]--;
  if (cnt[f[idx]] == 0) cur_ans--;
}

signed main() {
  // Tối ưu I/O cực đại cho C++
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  // Đọc mảng a và tiến hành Rời rạc hóa (Coordinate Compression)
  vector<int> vals;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    vals.push_back(a[i]);
  }
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
  }

  // Đọc đồ thị dạng cây (luôn có N-1 cạnh)
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // Khởi tạo trải phẳng cây
  dfs(1, 0);

  // Đọc các truy vấn cây con
  vector<Query> queries(n);
  for (int i = 0; i < n; i++) {
    queries[i].id = i;
    queries[i].l = st[i + 1];
    queries[i].r = en[i + 1];
  }

  // Sắp xếp truy vấn theo block
  sort(queries.begin(), queries.end(), cmp);

  // 4 Vòng lặp con trỏ cốt lõi của Mo
  int L = 1, R = 0;
  for (auto& query : queries) {
    // LUÔN ƯU TIÊN MỞ RỘNG (ADD) TRƯỚC KHI THU HẸP (REMOVE)
    while (L > query.l) add(--L);
    while (R < query.r) add(++R);
    while (L < query.l) remove(L++);
    while (R > query.r) remove(R--);

    ans[query.id] = cur_ans;
  }

  // In kết quả đúng thứ tự truy vấn ban đầu
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " ";
  }

  return 0;
}