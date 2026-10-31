#include <bits/stdc++.h>
using namespace std;

vector<int> cnt(100002, 0);
vector<int> adj[100002];


void dfs(int u) {
    for (auto v:adj[u]) {
        dfs(v);
        cnt[u] += cnt[v];
    }
    cnt[u] += 1;
}

int main() {
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
    stack<pair<int, int>> st;
    int ans = s.length();
    while(ans) {
        st.push({ans, cnt[ans]});
        ans = pi[ans - 1];
    }
    cout << st.size() << '\n';
    while(st.size()) {
        cout << st.top().first << ' ' << st.top().second << '\n';
        st.pop();
    }
}