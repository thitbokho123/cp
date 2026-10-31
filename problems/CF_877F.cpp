#include<bits/stdc++.h>
using namespace std;

#define int long long
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    vector<int> pref(n + 1);
    pref[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (a[i] == 2) {
            b[i] = -b[i];
        }
        pref[i] = b[i] + pref[i - 1];
    }
    block = sqrt(n);
    cin >> m;
    vector<Query> q(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> q[i].L >> q[i].R;
        q[i].pos = i;
    }
    sort(q.begin() + 1, q.end(), cmp);
    unordered_map<long long, int> f;
    f.reserve(2*n); 
    f.max_load_factor(0.7);
    int currL = 1, currR = 0;
    int res = 0;
    vector<int> ans(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        int L = q[i].L - 1, R = q[i].R;
        int x = q[i].pos;
        while (currL > L) {
            currL--;
            res += f[pref[currL] + k];
            f[pref[currL]]++;
            
        }
        while (currR < R) {
            currR++;
            res += f[pref[currR] - k]; 
            f[pref[currR]]++;
        }
        while (currL < L) {
            f[pref[currL]]--;res -= f[pref[currL] + k];
            currL++;
        }
        while (currR > R) {
            f[pref[currR]]--;
            res -= f[pref[currR] - k];
            currR--;
        }
        ans[x] = res;
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
}