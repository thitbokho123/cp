#include<bits/stdc++.h>
using namespace std;

int block;
int n, m, k;

struct Query {
    int L, R;
    int pos;
};

bool cmp(Query x, Query y) {
    if (x.L / block != y.L / block) {
        return x.L < y.L;
    }
    return x.R < y.R;
}

int main() {
    cin >> n >> m >> k;
    int a[n + 1];
    vector<int> pref(n + 1);
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = a[i] ^ pref[i - 1];
    }
    block = sqrt(n);
    vector<Query> q(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> q[i].L >> q[i].R;
        q[i].pos = i;
    }
    sort(q.begin() + 1, q.end(), cmp);
    vector<int> f(1000001, 0);
    f[pref[0]] = 1;
    int currL = 1, currR = 0;
    int res = 0;
    vector<int> ans(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        int L = q[i].L - 1, R = q[i].R;
        int x = q[i].pos;
        while (currL > L) {
            currL--;
            res += f[pref[currL] ^ k];
            f[pref[currL]]++;
            
        }
        while (currR < R) {
            currR++;
            res += f[pref[currR] ^ k]; 
            f[pref[currR]]++;
        }
        while (currL < L) {
            
            f[pref[currL]]--;res -= f[pref[currL] ^ k];
            currL++;
        }
        while (currR > R) {
            
            f[pref[currR]]--;
            res -= f[pref[currR] ^ k];
            currR--;
        }
        ans[x] = res;
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
}