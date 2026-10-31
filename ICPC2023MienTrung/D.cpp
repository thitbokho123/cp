#include <bits/stdc++.h>
using namespace std;

int n, m, k;
vector<string> a;

bool check(int V) {
    long long bomb = 0; 

    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < m) {
            if (a[i][j] == '#') { 
                j++; 
                continue; 
            }

            int L = j;
            vector<int> xs;
            while (j < m && a[i][j] != '#') {
                if (a[i][j] == 'x') xs.push_back(j);
                j++;
            }
            int R = j - 1;

            if (xs.empty()) continue;

            int idx = 0;
            while (idx < xs.size()) {
                int p = xs[idx];
                int c = min(R, p + V);
                int right = min(R, c + V);
                bomb++;
                idx = upper_bound(xs.begin() + idx, xs.end(), right) - xs.begin();
                if (bomb > k) return false;
            }
        }
    }

    return bomb <= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bool flag = false;
    for (auto &row : a) {
        for (char ch : row) {
            if (ch == 'x') {
                flag = true;
            }
        }
    }
    if (!flag) { 
        cout << 0 << "\n"; 
        return 0;
    }

    int lo = 0, hi = m, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            ans = mid;
            hi = mid - 1; 
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << "\n";
}
