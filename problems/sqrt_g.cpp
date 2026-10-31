#include<bits/stdc++.h>
using namespace std;

#define int long long

int n, q;
int a[200001];
int block;
int sum[5000];

void query(int x, int y) {
    sum[x / block] -= a[x];
    a[x] = y;
    sum[x / block] += a[x];
    for (int i = 1; i <= n; i++) {
        int temp = 0;
        for (int k = 0; k < i / block; k++) {
            temp += sum[k];
        }
        int l = (i / block) * block;
        for (int j = l; j < i; j++) {
            temp += a[j];
        }
        if (temp == a[i]) {
            cout << i << '\n';
            return;
        }
    }
    cout << -1 << '\n';
}

void preprocess() {
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i < n; i++) {
        sum[i / block] += a[i];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    block = sqrt(n);
    preprocess();
    while (q--) {
        int x, y;
        cin >> x >> y;
        query(x, y);
    }
}