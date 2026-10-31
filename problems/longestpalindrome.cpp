#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll mod = 1e9 + 7;
ll base = 31;
ll POW[100007], tHash[100007], sHash[100007];

ll getTHash(ll i, ll j) {
    ll res = (tHash[j] - tHash[i - 1] * POW[j - i + 1]) % mod;
    if (res < 0) res += mod;
    return res;
}

ll getSHash(ll i, ll j) {
    ll res = (sHash[j] - sHash[i - 1] * POW[j - i + 1]) % mod;
    if (res < 0) res += mod;
    return res;
}

signed main() {
    int n;
    cin >> n;
    string t;
    cin >> t;
    int lenT = t.size();
    string s = t;
    reverse(s.begin(), s.end());
    t = " " + t;
    s = " " + s;
    

    POW[0] = 1;

    for (int i = 1; i <= lenT; i++) {
        POW[i] = (POW[i - 1] * base) % mod;
    }

    for (int i = 1; i <= lenT; i++) {
        tHash[i] = (tHash[i - 1] * base + t[i] - 'a' + 1) % mod;
    }

    for (int i = 1; i <= lenT; i++) {
        sHash[i] = (sHash[i - 1] * base + s[i] - 'a' + 1) % mod;
    }

    int ans = 0;

    for (int i = 1; i <= lenT; i++) {
        int lo = 0, hi = min(i, lenT - i + 1), best = 0;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (getTHash(i - mid, i) == getSHash(lenT - i + 1 - mid, lenT - i + 1)) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        ans = max(ans, best * 2 + 1);
    }

    for (int i = 1; i <= lenT; i++) {
        int lo = 0, hi = min(i, lenT - i), best = 0;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (getTHash(i - mid + 1, i + mid) == getSHash(lenT - (i + mid) + 1, lenT - (i - mid + 1) + 1)) {
                best = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1; 
            }
        }
        ans = max(ans, best * 2);
    }
    cout << ans;
}