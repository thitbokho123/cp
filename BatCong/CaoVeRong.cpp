#include <bits/stdc++.h>
using namespace std;

int a[21];
int ans = 0;
int n, t;

void gen(int x) {
    if (x == n) {
        int countNail = 0;
        int notNail = 0;

        for (int i = 0; i < n; i++) {
            if ((i == 0) && (a[i] > a[i + 1])) {
                return;
            }

            if ((i == n - 1) && (a[i] > a[i - 1])) {
                return;
            }

            if ((i > 0) && (i < n - 1)) {
                if ((a[i - 1] < a[i]) && (a[i] > a[i + 1])) {
                    countNail++;
                }

                if ((a[i] == a[i - 1]) || (a[i] == a[i + 1])) {
                    return;
                }
            }

            if ((i > 1) && (i < n - 2)) {
                if ((a[i - 1] > a[i]) && (a[i] < a[i + 1])) {
                    notNail++;
                }
            }
        }

        if ((countNail == t) && (notNail == t - 1)) {
            ans++;
        }

        return;
    }
    
    for (int i = 1; i <= 4; i++) {
        a[x] = i;
        gen(x + 1);
    }
}

int main() {
    cin >> n >> t;
    gen(0);
    cout << ans;
}