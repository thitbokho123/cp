#include <bits/stdc++.h>
using namespace std;

vector<int>adj[1000];
int n, m;
bool vis[1000];

void dfs(int u) {
    vis[u] = true;
    for (int i = 0; i < adj[u].size(); i++) {
        if(!vis[adj[u][i]]) {
            dfs(adj[u][i]);
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
}