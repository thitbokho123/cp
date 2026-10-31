#include<bits/stdc++.h>
using namespace std;

#define int long long

int n,m;
vector<int>g[10001];
int timeDfs=0;
int low[10001],num[10001];
stack<int>st;
bool deleted[10001];
int scc=0;

void dfs(int u)
{
    low[u]=num[u]=++timeDfs;
    st.push(u);
    for(auto v:g[u])
    {
        if(deleted[v]) continue;
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
    if(low[u]==num[u])
    {
        scc++;
        int v;
        do
        {
            v=st.top();
            deleted[v]=1;
            st.pop();
        } while (v!=u);
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
    {
        if(!num[i]) dfs(i);
    }
    cout<<scc;
}