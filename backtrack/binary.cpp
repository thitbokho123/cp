#include<bits/stdc++.h>
using namespace std;
int arr[20],n;
void ans()
{
    for(int i=0;i<n;i++)
        cout<<arr[i];
    cout<<'\n';
}
void backtrack(int i)
{
    if(i==n) ans();
    else
    {
        for(int j=0;j<=1;j++)
        {
            arr[i]=j;
            backtrack(i+1);
        }
    }
}
int main()
{
    cin>>n;
    backtrack(0);
}