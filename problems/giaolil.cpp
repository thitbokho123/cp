#include<bits/stdc++.h>
using namespace std;

const int MAXN=256;
const int INF=1e9+7;
int n,m;
int d[MAXN],c[MAXN][MAXN],f[MAXN][MAXN],maxFlow;
vector<int>adj[MAXN];
int curVertexId[MAXN];

void bfs(int s){
    fill(d,d+n+1,INF);
    queue<int>bfsQueue;
    bfsQueue.push(s);
    while(!bfsQueue.empty()){
        int u=bfsQueue.top();
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
    if(curDelta==0) continue;
    if(u==t) continue;

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
    cin>>n;
    int a[n+1][n+1];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            adj[i].push_back(2*n+j);
            adj[2*n+j].push_back(i);
            c[i][2*n+j]=-a[i][j];
        }
    }
    maxFlow=0;
    while(true){
        bfs();
        if(d[n]==INF) break;
        for(int i=1;i<=n;i++) curVertexId[i]=0;
        while(int delta=dfs(s,INF)){
            maxFlow+=delta;
        }
    }
    cout<<-maxFlow;
}