#include<bits/stdc++.h>
using namespace std;

#define int long long
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

int floodfill(int x, int y, int color1, int color2)
{
    if(a[x][y]!=color1) return 0;
    else
    {
        int sum=1;
        for(int i=0;i<4;i++)
        {
            sum+=floodfill(x+dx[i],y+dy[i],color1,color2);
        }
        return sum;
    }
}

signed main()
{

}