#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    // build pi cho t
    vector<int> pi(m, 0);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && t[i] != t[j]) j = pi[j - 1];
        if (t[i] == t[j]) j++;
        pi[i] = j;
    }

    // build automaton next[state][c]
    vector<vector<int>> next(m + 1, vector<int>(26, 0));
    for (int state = 0; state <= m; state++) {
        for (int c = 0; c < 26; c++) {
            if (state < m && t[state] - 'a' == c) {
                next[state][c] = state + 1;
            } else {
                if (state == 0) next[state][c] = 0;
                else next[state][c] = next[pi[state - 1]][c];
            }
        }
    }

    // dp
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == -1) continue;
            if (s[i] == '?') {
                for (int c = 0; c < 26; c++) {
                    int nj = next[j][c];
                    int add = (nj == m ? 1 : 0);
                    dp[i+1][nj] = max(dp[i+1][nj], dp[i][j] + add);
                }
            } else {
                int nj = next[j][s[i] - 'a'];
                int add = (nj == m ? 1 : 0);
                dp[i+1][nj] = max(dp[i+1][nj], dp[i][j] + add);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= m; j++) ans = max(ans, dp[n][j]);
    cout << ans;
}
