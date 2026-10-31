#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N=1e5+2, M=2e5+2;

struct Edge
{
    int targett, id;
    Edge(int _target, int _id): target(_target),id(_id) {}
};

vector<Edge> adj[N];
bool used_edge[M];
int n,m,in_deg[N];

list <int> euler_walk(int u)
{
    list <int>ans;
    ans.push_back(u);

    while(!adj[u].empty)
    {
        int v=adj[u].back().target;
        int eid==adj[u].back().id;
        adj[u].pop_back();
        if(used_edge[v]) continue;
        used_edge[v]=true;
        u=v;
        ans.push_back(u);
    }
    for(auto it=++ans.begin();it!=ans.end();++it)
    {
        auto t=euler_walk(*it);
        t.pop_back();
        ans.splice(it,t);
    }
    return ans;
}

bool check()
{
    if((adj[1].size()!=in_deg[1]+1)||(adj[n].size()!=in_deg[n]-1))
    {
        return false;
    }
    for(int i=2;i<n;i++)
    {
        if(adj[i].size!=in_deg[i])
        {
            return false;
        }
    }
    return true;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].emplace_back(v,i);
        ++in_deg[v];
    }
    if(!check) cout<<"IMPOSSIBLE";
    else
    {
        adj[n].emplace_back(1,m);
        list<int>ans=euler_walk(1);
        if(ans.size()<m+1) cout<<"IMPOSSIBLE";
        else
        {
            for(auto u1=ans.begin(),u2=++ans.begin();u2!=ans.end();++u1,++u2)
            {
                if(*u1==n&&*u2==1)
                {
                    for(auto i=u2;i!=ans.end();++i)
                    {
                        cout<<(*i)<<' ';
                    }
                    for(auto i=++ans.begin();i<u2;++i)
                    {
                        cout<<(*i)<<' ';
                    }
                }
                break;
            }
        }
    }
}