#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int l[n + 1];
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> l[i];
        mx += l[i];
    }
    sort(l + 1, l + n + 1);
    int dp[n + 1][mx + 1];
    memset(dp[n + 1], 0, sizeof(dp[n + 1]));
    for (int i = 1; i <= n; i++) {
        dp[i][l[i]] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= mx; j++) {
            for (int k = 1; k <= i; k++) {
                dp[i][j] += dp[k][j - l[k]];
                dp[i][j] %= mod;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < l[i]; j++) {
            ans += dp[n][j];
            ans %= mod;
        }
    }
    cout << ans;
}