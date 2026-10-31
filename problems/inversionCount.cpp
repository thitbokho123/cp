#include<bits/stdc++.h>
using namespace std;

#define int long long

int n;
int a[60005];
int block;
vector<vector<int>> v;

signed main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    block = sqrt(n);
    v.resize((n + block - 1) / block);
    for (int i = 0; i < n; i++) {
        v[i / block].push_back(a[i]);
    }
    for (int i = 0; i < v.size(); i++) {
        sort(v[i].begin(), v[i].end());
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < v.size(); j++) {
            if (j < i / block) {
                auto it = upper_bound(v[j].begin(), v[j].end(), a[i]);
                ans += (v[j].end() - it);
            } else if (j > i / block) {
                auto it = lower_bound(v[j].begin(), v[j].end(), a[i]);
                ans += (it - v[j].begin());
            } else {
                int b = i / block;
                for (int k = b * block; k < min(n, b * block + block); k++) {
                    if (a[k] > a[i] && k < i) {
                        ans++;
                    } else if (a[k] < a[i] && k > i) {
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans / 2;
}