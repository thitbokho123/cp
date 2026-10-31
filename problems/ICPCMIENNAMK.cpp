#include <bits/stdc++.h>
using namespace std;

int n;
int a[50001];

bool check(int x) {
    for (int i = x; i <= n - x + 1; i++) {
        bool flag = 0;
        if (a[i] < x) {
            continue;
        }
        for (int j = 1; j < x; j++) {
            if (a[i - j] < x - j || a[i + j] < x - j) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int hi = -1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        hi = max(a[i], hi);
    }
    int lo = 1;
    int ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << ans;
}