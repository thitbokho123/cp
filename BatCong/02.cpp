#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    int n;
    cin >> n;

    int a[n + 1], b[n + 1];

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(b + 1, b + n + 1);
    int dp[n + 1];

    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j] += abs(a[i] - b[j]); // dp[j] la chi phi nho nhat ma khi gan a[i] = b[j]
            if (j > 1) {
                dp[j] = min(dp[j], dp[j - 1]); //vi dp[j-1] la chi phi nho nhat khi gan a[i]=b[j-1]
            }
        }
    }
    cout << dp[n];
}