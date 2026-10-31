#include<bits/stdc++.h>
using namespace std;

#define int long long 
int n,m;
int timeDfs=0;
int num[10001],low[10001],tail[10001];
vector<int>g[10001];

void dfs(int u, int pre)
{
    num[u]=low[u]=++timeDfs;
    for(int v:g[u])
    {
        if(v==pre) continue;
        if(!num[v])
        {
            dfs(v,u);
            low[u]=min(low[u],low[v]);
        }
        else{
            low[u]=min(low[u],num[v]);
        }
    }
    tail[u]=timeDfs;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
    {
        if(!num[i]) dfs(i,i);
    }
}