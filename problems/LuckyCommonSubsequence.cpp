#include <bits/stdc++.h>
using namespace std;

// Lưu vết
struct State {
    int pi, pj, pk;
    char c;
};

int main() {
    string s1, s2, virus;
    cin >> s1 >> s2 >> virus;

    int n = s1.length(), m = s2.length(), L = virus.length();

    vector<int> pi(L, 0);
    for (int i = 1, j = 0; i < L; i++) {
        while (j > 0 && virus[i] != virus[j]) j = pi[j-1];
        if (virus[i] == virus[j]) j++;
        pi[i] = j;
    }

    vector<vector<int>> aut(L+1, vector<int>(26, 0));
    for (int state = 0; state <= L; state++) {
        for (int c = 0; c < 26; c++) {
            if (state < L && c == virus[state]-'A') aut[state][c] = state+1;
            else if (state > 0) aut[state][c] = aut[pi[state-1]][c];
            else aut[state][c] = 0;
        }
    }

    // dp[i][j][k]
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m+1, vector<int>(L, 0)));
    vector<vector<vector<State>>> parent(n+1, vector<vector<State>>(m+1, vector<State>(L, {-1,-1,-1,0})));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < L; k++) {
                if (s1[i] == s2[j]) {
                    int c = s1[i] - 'A';
                    int nk = aut[k][c];
                    if (nk < L && dp[i+1][j+1][nk] < dp[i][j][k] + 1) {
                        dp[i+1][j+1][nk] = dp[i][j][k] + 1;
                        parent[i+1][j+1][nk] = {i, j, k, s1[i]};
                    }
                }
                if (dp[i+1][j][k] < dp[i][j][k]) {
                    dp[i+1][j][k] = dp[i][j][k];
                    parent[i+1][j][k] = {i, j, k, 0};
                }
                if (dp[i][j+1][k] < dp[i][j][k]) {
                    dp[i][j+1][k] = dp[i][j][k];
                    parent[i][j+1][k] = {i, j, k, 0};
                }
            }
        }
    }

    int mx = 0;
    State mxState = {-1,-1,-1,0};
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k < L; k++) {
                if (dp[i][j][k] > mx) {
                    mx = dp[i][j][k];
                    mxState = {i, j, k, 0};
                }
            }
        }
    }

    string res;
    State cur = mxState;
    while (cur.pi != -1) {
        if (cur.c != 0) res.push_back(cur.c);
        cur = parent[cur.pi][cur.pj][cur.pk];
    }
    reverse(res.begin(), res.end());

    if (res.empty()) cout << 0 << "\n";
    else cout << res << "\n";
}
