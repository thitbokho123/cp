#include<bits/stdc++.h>
using namespace std;

#define int long long
const int maxn 10005
int par[maxn],sz[maxn],rank[maxn];

void makeset(int v)
{
    par[v]=v;
    sz[v]=1;
}

int findset(int v)
{
    if(v==par[v]) return v;
    int p=findset(par[v]);
    par[v]=p;
    return p;
}

void join(int a, int b)
{
    a=findset(a);
    b=findset(b);
    if(a!=b)
    {
        if(sz[a]<sz[b]) swap(a,b);
        par[b]=a;
        sz[a]+=sz[b];
    }
}

signed main()
{
    
}