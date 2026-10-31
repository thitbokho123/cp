#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n + 1]; 
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        sort(a + 1, a + n + 1); 

        if (n == 1) {
            if (a[1] == 1) { 
                cout << "RR\n";
            } else { 
                cout << "Hieu\n";
            }
            continue;
        }

        int c = a[n - 2] - n + 1;
        int d = a[n - 1] - n;
        if (c == d && d % 2 == 0) {
            cout << "RR\n";
        } else {
            cout << "Hieu\n";
        }
    }
}
