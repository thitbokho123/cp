#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, m;
#define maxN 1000
int d[maxN], par[maxN];
bool vis[maxN];
vector<int> g[maxN];

void bfs(int s)
{
    fill_n(d, maxN, 0);
    fill_n(par, maxN, -1);
    fill_n(vis, maxN, false);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : g[u])
        {
            if (!vis[v])
            {
                d[v] = d[u] + 1;
                par[v] = u;
                vis[v] = true;
                q.push(v);
            }
        }
    }
}

void trace(int u)
{
    if (!vis[u])
        cout << "No path";
    else
    {
        vector<int> path;
        for (int v = u; v != -1; v = par[v])
        {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        for (auto v : path)
            cout << v << ' ';
    }
}

signed main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs(1);
    cout<<d[4];
}
