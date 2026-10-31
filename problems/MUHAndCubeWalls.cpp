#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    int b[n], e[w];
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int j = 0; j < w; j++) {
        cin >> e[j];
    }
    if (w == 1) {
        cout << n;
        return 0;
    }
    int s[n - 1], t[w - 1];
    for (int i = 0; i < n - 1; i++) {
        s[i] = b[i + 1] - b[i];
    }
    for (int j = 0; j < w - 1; j++) {
        t[j] = e[j + 1] - e[j];
    }
    vector<int> pi(w, 0);
    int j = 0;
    for (int i = 1; i < w - 1; i++) {
        while (j > 0 && t[i] != t[j]) {
            j = pi[j - 1];
        }
        if (t[i] == t[j]) {
            j++;
        }
        pi[i] = j;
    }

    j = 0;
    int ans = 0;

    for (int i = 0; i < n - 1; i++) {
        while (j > 0 && t[j] != s[i]) {
            j = pi[j - 1];
        }
        if (t[j] == s[i]) {
            j++;
        }
        if (j == w - 1) {
            j = pi[j - 1];
            ans++;
        }
    }
    cout << ans;
}