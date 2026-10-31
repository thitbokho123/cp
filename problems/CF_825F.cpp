#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.length();
    vector<int> dp(n + 1, 0);

    vector<vector<int>> kmp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int k = kmp[i][j - 1];
            while (k > 0 && s[j] != s[i + k]) {
                k = kmp[i][i + k - 1];
            }
            if (s[j] == s[i + k]) {
                k++;
            }
            kmp[i][j] = k;
        }
    }

    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        dp[i] = i + 1;

        for (int j = 1; j <= i; j++) {
            int len = i - j + 1;
            int x = kmp[j - 1][i - 1];
            int p = len - x;

            int z;
            if (len % p == 0 && len / p > 1) {
                int k = len / p;
                int y = to_string(k).length();
                z = y + p;
            } else {
                z = len + 1;
            }
            
            dp[i] = min(dp[i], dp[j - 1] + z);
        }
    }

    cout << dp[n];

}