#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string a, b, s;
    cin >> a >> b >> s;
    string t = s;
    reverse(t.begin(), t.end());
    reverse(b.begin(), b.end());
    
    vector<int> zS(m + n + 1, 0);
    int l = 0, r = 0;

    a = s + "$" + a;

    for (int i = 0; i < m + n + 1; i++) {
        if (i <= r) {
            zS[i] = min(r - i + 1, zS[i - l]);
        }
        while (i + zS[i] < a.length() && a[zS[i]] == a[i + zS[i]]) {
            zS[i]++;
        }
        if (i + zS[i] - 1 > r) {
            l = i;
            r = i + zS[i] - 1;
        }
        cout << zS[i] <<' ';
    }
    cout << '\n';

    b = t + "$" + b;

    l = 0, r = 0;
    vector<int> zT(m + n + 1, 0);
    for (int i = 0; i < m + n + 1; i++) {
        if (i <= r) {
            zT[i] = min(r - i + 1, zT[i - l]);
        }
        while (i + zT[i] < b.length() && b[zT[i]] == b[i + zT[i]]) {
            zT[i]++;
        }
        if (i + zT[i] - 1 > r) {
            l = i;
            r = i + zT[i] - 1;
        }
        cout <<zT[i]<<' ';
    }
    cout<<'\n';

    vector<int> diffA(m + 2, 0);
    vector<int> diffB(m + 2, 0);
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int x = zS[i + m + 1];
        int y = zT[i + m + 1];
        if (x) {
            diffA[1] += 1;
            diffA[x + 1] -= 1;
        }
        if (y) {
            diffB[1] += 1;
            diffB[y + 1] -= 1;
        }
        if (x == m) {
            ans++;
        }
        if (y == m) {
            ans++;
        }
    }
    
    vector<int> cntA(m + 2, 0);
    vector<int> cntB(m + 2, 0);
    for (int i = 1; i <= m; i++) {
        cntA[i] = cntA[i - 1] + diffA[i];
        cntB[i] = cntB[i - 1] + diffB[i];
    }for (int i = 0; i <= m; i++) {
        cout << cntA[i] << ' ';
    }
    cout<<"\n";
    for (int j = 0;j<=m;j++) {
        cout<<cntB[j]<<' ';
    }
    cout<<"\n";
    for (int i = 1; i < m; i++) {
        ans += cntA[i] * cntB[m - i];
    }
    cout << ans;
}