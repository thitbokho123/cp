#include<bits/stdc++.h>
using namespace std;

#define int long long

int n,m;
vector<int>g[10001];
int num[10001],low[10001];
int vis[10001];
int timeDfs=0;
vector<int>topo;

void dfs(int u)
{
    vis[u]=1;
    low[u]=num[u]=++timeDfs;
    for(auto v:g[u])
    {
        if(vis[v]==1) continue;
        if(!num[v])
        {
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else
        {
            low[u]=min(low[u],num[v]);
        }
    }
    topo.push_back(u);
    vis[u]=2;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i]) dfs(i);
    }
    reverse(topo.begin(),topo.end());
    for(int i=0;i<topo.size();i++)
    {
        cout<<topo[i]<<' ';
    }
}