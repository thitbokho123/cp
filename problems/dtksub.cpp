#include <bits/stdc++.h>
using namespace std;

#define int long long

int mod = 1e9 + 7;
int base = 31;
int POW[50007], sHash[50007];
int sz = 0;
int n, k;

int getHash(int i, int j) {
    return ((sHash[j] - sHash[i - 1] * POW[j - i + 1]) + mod * mod) % mod;
}

bool check(int mid) {
    map <int, int> mp;
    for (int i = 1; i <= sz - mid; i++) {
        mp[getHash(i, i + mid - 1)]++;
        if (mp[getHash(i, i + mid - 1)] == k) {
            return true;
        }
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> k;

    string s;
    cin >> s;

    s = " " + s;
    sz = s.length();

    POW[0] = 1;

    for (int i = 1; i <= s.length() - 1; i++) {
        POW[i] = (POW[i - 1] * base) % mod;
    }

    for (int i = 1; i <= s.length() - 1; i++) {
        sHash[i] = ((sHash[i - 1] * base) % mod + s[i] - 'a' + 1) % mod;
    }

    int lo = 0, hi = s.length(), best = 0;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << best;
}