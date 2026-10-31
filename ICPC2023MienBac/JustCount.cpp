#include <bits/stdc++.h>
using namespace std;

const int MOD = 123456789;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 

    int n, m, k;
    cin >> n >> m >> k;

    if (m > n) {
        swap(n, m);
    }

    vector<int> masks;
    for (int mask = 0; mask < (1 << m); ++mask) {
        if ((mask & (mask << 1)) == 0) {
            masks.push_back(mask);
        }
    }

    vector<vector<int>> dp(1 << m, vector<int>(k + 1, 0));

    for (int mask : masks) {
        int popcount = __builtin_popcount(mask);
        if (popcount <= k) {
            dp[mask][popcount] = 1;
        }
    }

    for (int i = 2; i <= n; ++i) {
        vector<vector<int>> new_dp(1 << m, vector<int>(k + 1, 0));
        
        for (int cur_mask : masks) {
            int popcount_cur = __builtin_popcount(cur_mask);

            for (int prev_mask : masks) {
                if ((cur_mask & prev_mask) || 
                    (cur_mask & (prev_mask << 1)) || 
                    (cur_mask & (prev_mask >> 1))) {
                    continue;
                }

                for (int j = popcount_cur; j <= k; ++j) {
                    if (dp[prev_mask][j - popcount_cur] > 0) {
                        new_dp[cur_mask][j] = (new_dp[cur_mask][j] + dp[prev_mask][j - popcount_cur]) % MOD;
                    }
                }
            }
        }
        dp = new_dp;
    }

    int ans = 0;
    for (int mask : masks) {
        ans = (ans + dp[mask][k]) % MOD;
    }

    cout << ans;
}