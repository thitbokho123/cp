#include<bits/stdc++.h>
using namespace std;

int block;
int n;

struct Query {
    int L, R;
    int pos;
};

bool cmp (Query x, Query y){
    if (x.L/block != y.L/block) {
        return x.L/block < y.L/block;
    }
    return x.R < y.R;
}

int main() {
    cin >> n;
    int a[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    block = sqrt(n);
    int m;
    cin >> m;
    Query q[m + 1];
    for (int i = 1; i <= m; i++) {
        cin >> q[i].L >> q[i].R;
        q[i].pos = i;
    }
    sort(q + 1, q + m + 1, cmp);
    int f[1000001];
    int currL = 0, currR = 0;
    int cnt = 0;
    memset(f, 0, sizeof(f));
    int ans[m + 1];
    for (int i = 1; i <= m; i++) {
        int L = q[i].L, R = q[i].R;
        while (currL < L) {
            if (f[a[currL]] > 0) {
                f[a[currL]]--;
                if (f[a[currL]] == 0) {
                    cnt--;
                }
            }
            currL++;
        }

        while (currL > L) {
            f[a[currL]]++;
            if (f[a[currL]] == 1) {
                cnt++;
            }
            currL--;
        }

        while (currR <= R) {
            f[a[currR]]++;
            if(f[a[currR]] == 1) {
                cnt++;
            }
            currR++;
        }

        while (currR > R + 1) {
            if (f[a[currR]] > 0) {
                f[a[currR]]--;
                if (f[a[currR]] == 0) {
                    cnt--;
                }
            }
            currR--;
        }
        ans[q[i].pos] = cnt;
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
}