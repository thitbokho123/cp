#include <bits/stdc++.h>
using namespace std;

#define int long long
int base = 31;
int mod = 1e9 + 7;
int POW[1000007], Hash[1000007];

int getHash(int i, int j) {
    return ((Hash[j] - Hash[i - 1] * POW[j - i + 1]) % mod + mod * mod) % mod;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s;
    cin >> s;
    int len = s.length();
    s = " " + s;
    POW[0] = 1;
    for (int i = 1; i <= len; i++) {
        POW[i] = (POW[i - 1] * base) % mod;
    }

    for (int i = 1; i <= len; i++) {
        Hash[i] = (Hash[i - 1] * base + s[i] - 'a' + 1) % mod;
    }

    vector<int> valid;

    for (int i = 2; i <= len; i++) {
        if((len - 1) % (i - 1) == 0) {
            valid.push_back(i);
        }
    }

    int lo = 0, hi = valid.size(), ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int first = getHash(1, valid[mid]);
        bool flag = true;
        for (int i = valid[mid]; i <= len - valid[mid] + 1; i += valid[mid] - 1) {
            if (first != getHash(i, i + valid[mid] - 1)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ans = valid[mid];
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans;
}