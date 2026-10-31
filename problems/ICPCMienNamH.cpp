#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    bool flag = 0;
    vector<int> v;
    for (int i = 1; i <= sqrt(c); i++) {
        if (i % a == 0 && i % b && d % i && c % i == 0) {
            cout << i;
            flag = 1;
            return 0;
        } 
        if (c % i == 0) {
            int k = c / i;
            if (k % a == 0 && k % b && d % k) {
                v.push_back(k);
            }
        }
    }
    sort(v.begin(), v.end());
    if (!flag && v.empty()) cout << -1;
    else cout << v[0];
}