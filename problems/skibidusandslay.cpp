#include<bits/stdc++.h>
using namespace std;

#define int long long
#pragma "Ofast"

const int maxn=500001;
int n,a[maxn];
vector<int>adj[maxn];
bool flag[maxn];

void solve()
{
    fill_n(a,n+1,sizeof(a));
    fill_n(flag,n+1,false);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++)
    {
        map<int,int>mp;
        for(auto v:adj[i])
        {
            mp[a[v]]++;
        }
        mp[a[i]]++;
        for(auto [c,b]:mp)
        {
            if(b>=2) flag[c]=1;
        }
    }
    for(int i=1;i<=n;i++) cout<<flag[i];
    cout<<'\n';
}

signed main()
{ 
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
}