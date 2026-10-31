#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[20][180][2];

int G(int idx, int sum, int tight, vector<int> &digit)
{
    if(idx==-1) return sum;
    if(dp[idx][sum][tight]!=-1&&tight!=1)
    {
        return dp[idx][sum][tight];
    }
    int k=(tight) ? digit[idx]:9;
    int ret=0;
    for(int i=0;i<=k;i++)
    {
        int newtight=(digit[idx]==i) ? tight:0;
        ret+=G(idx-1,sum+i,newtight,digit);
    }
    if(!tight) dp[idx][sum][tight]=ret;
    return ret;
}

int solve(int x)
{
    memset(dp,-1,sizeof(dp));
    vector<int>digit;
    while(x)
    {
        digit.push_back(x%10);
        x/=10;
    }
    return G(digit.size()-1,0,1,digit);
}

signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b;
        cin>>a>>b;
        cout<<solve(b)-solve(a-1)<<'\n';
    }
    
}