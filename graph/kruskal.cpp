#include<bits/stdc++.h>
using namespace std;

#define int long long

struct Edge{
    int u,v,c;
    Edge(int _u, int _v, int _c): u(_u), v(_v), c(_c) {};
};

struct Dsu{
    vector<int>par;

    void init(int n)
    {
        par.resize(n+5,0);
        for(int i=1;i<=n;i++)
        {
            par[i]=i;
        }
    }

    int find_set(int v)
    {
        if(v==par[v]) return v;
        return par[v]=find_set(par[v]);
    }

    bool join_set(int a, int b)
    {
        a=find_set(a);
        b=find_set(b);
        if(a==b) return false;
        par[b]=a;
        return true;
    }
} dsu;


int n,m,totalweight=0;
vector<Edge>edges;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v,c;
        cin>>u>>v>>c;
        edges.push_back({u,v,c});
    }
    dsu.init(n);
    sort(edges.begin(),edges.end(),[](Edge &x,Edge &y)
    {
        return x.c<y.c;
    });
    for(auto e:edges)
    {
        if(!dsu.join_set(e.u,e.v)) continue;
        totalweight+=e.c;
    }
    cout<<totalweight;
}