#include <bits/stdc++.h>
using namespace std;

int dist[1000];
vector<pair<int,int>>adj[1000];
int n, m;

void dijkstra(int s) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
    for (int i = 1; i <= n; i++) {
        dist[i] = 1000000007;
    }
    dist[s] = 0;
    pq.push({0,s});
    while (pq.size()) {
        int u = pq.top().second;
        pq.pop();
        for (auto v:adj[u]) {
            int v1 = v.first;
            int v2 = v.second;
            
            if (dist[v2] > dist [u] + v1) {
                dist[v2] = dist[u] + v1;
                pq.push({dist[v2], v2});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    dijkstra(1);
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << ' ';
    }
}