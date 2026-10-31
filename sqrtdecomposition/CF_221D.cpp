#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int n, m;
int cnt[N];
vector<vector<int>> prefix_sums;
int a[N];
vector<int> values;

void init() {
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] <= n) {
            cnt[a[i]]++;
        }
    }
    for (int x = 1; x <= n; x++) {
        if (cnt[x] >= x) {
            values.push_back(x);
            vector<int> prefix_sum(n + 1);
            for (int i = 1; i <= n; i++) {
                prefix_sum[i] = prefix_sum[i - 1] + (a[i] == x);
            }
            prefix_sums.push_back(prefix_sum);
        }
    }
}

int query(int l, int r) {
    int ans = 0;
    for (int i = 0; i < values.size(); i++) {
        if (prefix_sums[i][r] - prefix_sums[i][l - 1] == values[i]) {
            ans++;
        }
    }
    return ans;
}

int main() {
    cin >> n >> m;
    init();
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
}