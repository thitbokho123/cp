#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    vector<int>ans;
    ans.push_back(a[0]);
    for(int i=0;i<n;i++)
    {
        if(a[i]>ans.back())
        {
            ans.push_back(a[i]);
        }
        else
        {
            int x=(lower_bound(ans.begin(),ans.end(),a[i])-a.begin());
            ans[x]=a[i];
        }
    }
    for(int i=0;i<ans.size();i++)
    {
        cout<<ans[i]<<" ";
    }
}