#include<bits/stdc++.h>
using namespace std;
int n,a[20];
bool check[20];
void backtrack(int i)
{
    if(i==n+1)
    {
        for(int k=1;k<=n;k++)
        {
            cout<<a[k]<<' ';
        }
        cout<<'\n';
    }
    else
    for(int j=1;j<=n;j++)
    {
        if(!check[j])
        {
            a[i]=j;
            check[j]=1;
            backtrack(i+1);
            check[j]=0;
        }
    }
}
int main()
{
    cin>>n;
    backtrack(1);
}