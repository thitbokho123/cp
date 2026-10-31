#include<bits/stdc++.h>
using namespace std;

const int MAXN=1001;
const int INF=1e9+7;

int n,m,s,t;
vector<int>adj[MAXN];
int c[MAXN][MAXN], f[MAXN][MAXN],d[MAXN],maxFlow;

int curVertexId[MAXN];

void bfs(){
    fill(d,d+n+1,INF);
    d[s]=0;
    queue<int>bfsQueue;
    bfsQueue.push(s);
    while(!bfsQueue.empty()){
        int u=bfsQueue.front();
        bfsQueue.pop();
        for(auto v:adj[u]){
            if(d[v]!=INF) continue;
            if(f[u][v]-c[u][v]==0) continue;
            d[v]=d[u]+1;
            bfsQueue.push(v);
        }
    }
}

int dfs(int u, int curDelta){
    if(curDelta==0) return 0;
    if(u==t) return curDelta;

    for(;curVertexId[u]<adj[u].size();curVertexId[u]++){
        int v=adj[u][curVertexId[u]];

        if(d[v]!=d[u]+1) continue;
        if(f[u][v]==c[u][v]) continue;

        int delta=dfs(v,min(c[u][v]-f[u][v],curDelta));
        if(delta==0) continue;
        f[u][v]+=delta;
        f[v][u]-=delta;
        return delta;
    }
    return 0;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>n>>m>>s>>t;
    for(int u,v,i=1;i<=m;i++){
        cin>>u>>v;
        cin>>c[u][v];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    maxFlow=0;
    while(true){
        bfs();
        if(d[t]==INF) break;
        for(int i=1;i<=n;i++) curVertexId[i]=0;
        while(int delta=dfs(s,INF)){
            maxFlow+=delta;
        }
    }
    cout<<maxFlow;
}
