#include <bits/stdc++.h>
using namespace std;

int main() {
    string x, y;
    cin >> x >> y;

    vector<int> pi(y.length() + 1, 0);
    int j = 0;

    for (int i = 1; i < y.length(); i++) {
        while (j > 0 && y[i] != y[j]) {
            j = pi[j - 1];
        }
        if (y[i] == y[j]) {
            j++;
        }
        pi[i] = j;
    }

    vector<vector<int>> aut(y.length() + 1, vector<int> (26, 0));

    for (int state = 0; state <= y.length(); state++) {
        for (int c = 0; c < 26; c++) {
            if (state < y.length() && y[state] - 'a' == c) {
                aut[state][c] = state + 1;
            } else {
                if (state == 0) aut[state][c] = 0;
                else aut[state][c] = aut[pi[state - 1]][c];
            }
        }
    }

    vector<vector<int>> dp(x.length() + 1, vector<int>(y.length() + 1, 1e9 + 7));
    dp[0][0] = 0;

    for (int i = 0; i < x.length(); i++) {
        for (int j = 0; j <= y.length(); j++) {
            if (dp[i][j] == 1e9 + 7) continue;
            int nx = aut[j][x[i] - 'a'];
            if (nx == y.length()) {
                dp[i + 1][pi[nx - 1]] = min(dp[i + 1][pi[nx - 1]], dp[i][j] + 1);
            } else {
                dp[i + 1][nx] = min(dp[i + 1][nx], dp[i][j]);
            }
        }
    }

    int ans = 1e9 + 7;
    for (int i = 0; i <= y.length(); i++) {
        ans = min(ans, dp[x.length()][i]);
    }
    cout << ans;
}