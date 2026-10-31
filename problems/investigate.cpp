#include<bits/stdc++.h>
using namespace std;

#define int long long
int n,m;
vector<vector<int>>adj;
int timeDfs=0;
vector<int>low,num,tail;

void dfs(int u, int pre)
{
    low[u]=num[u]=++timeDfs;
    for(int v:adj[u])
    {
        if(v==pre) continue;
        if(!num[v])
        {
            dfs(v,u);
            low[u]=min(low[u],low[v]);
        }
        else
        {
            low[u]=min(low[u],num[v]);
        }
    }
    tail[u]=timeDfs;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(false); cout.tie(false);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(!num[i])
        {
            dfs(i,0);
            cnt++;
        }
    }
    
}