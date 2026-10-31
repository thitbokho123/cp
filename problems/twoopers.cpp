#include <bits/stdc++.h>
using namespace std;

#define int long long

int base = 31;
int mod = 1e9 + 7;
int sHash[1000007], tHash[1000007], POW[1000007];

int getSHash(int i, int j) {
    return (((sHash[j] - sHash[i - 1] * POW[j - i + 1])) % mod + mod * mod) % mod;
}

int getTHash(int i, int j) {
    return (((tHash[j] - tHash[i - 1] * POW[j - i + 1])) % mod + mod * mod) % mod;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s, t;
    cin >> s >> t;
    int len = s.length();
    s = " " + s + s;
    t = " " + t;
    POW[0] = 1;
    for (int i = 1; i <= len * 2; i++) {
        POW[i] = (POW[i - 1] * base) % mod;
    }
    for (int i = 1; i <= len; i++) {
        tHash[i] = (tHash[i - 1] * base + t[i] - 'a' + 1) % mod;
    }

    int thash = getTHash(1, len);

    for (int i = 1; i <= 2 * len; i++) {
        sHash[i] = (sHash[i - 1] * base + s[i] - 'a' + 1) % mod;
    }

    int ans = 0;

    for (int i = 1; i <= len; i++) {
        if (getSHash(i, i + len - 1) == thash) {
            ans += len;
        } else {
            int lo = 1, hi = len, best = 0;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (getSHash(i, i + mid - 1) == getTHash(1, mid)) {
                    best = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (best < len && s[i + best] != t[best + 1]) {
                if (getSHash(i + best + 1, i + len - 1) == getTHash(best + 2, len)) {
                    ans++;
                }
            }
        }
    }
    cout << ans;
}