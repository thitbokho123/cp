#include <bits/stdc++.h>
using namespace std;

vector<int> cnt(1000002, 0);
vector<vector<int>> adj(1000002, vector<int>());


void dfs(int u) {
    for (auto v:adj[u]) {
        dfs(v);
        cnt[u] += cnt[v];
    }
    cnt[u] += 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s;
    cin >> s;
    vector<int> pi(s.length() + 1, 0);

    int j = 0;

    for (int i = 1; i < s.length(); i++) {
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }

    for (int i = 0; i < s.length(); i++) {
        adj[pi[i]].push_back(i + 1);
    }
    dfs(0);
    int ans = s.length();
    int res = 0;
    while(ans) {
        if (cnt[ans] >= 3) {
            res = max(ans, res);
        }
        ans = pi[ans - 1];
    }
    if (!res) {
        cout << "Just a legend";
        return 0;
    }
    for (int i = 0; i < res; i++) {
        cout << s[i];
    }
}