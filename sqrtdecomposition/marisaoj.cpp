#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1000111;
const ll MOD = 1000000007;
const ll BASE = 31;

string T;
vector<string> S;
vector<int> lengths;           // Các độ dài khác nhau của các xâu trong S
unordered_set<ll> H[MAXN];     // H[i] lưu hash của các xâu độ dài i
ll POW[MAXN];                  // POW[i] = BASE^i % MOD
ll hashT[MAXN];                // prefix hash của T
int64_t countT[MAXN];          // DP

// Tính hash của substring T[l..r] (1-based)
ll get_hash(int l, int r){
    return (hashT[r] - hashT[l-1] * POW[r-l+1] % MOD + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    S.resize(n);
    for(int i = 0; i < n; i++){
        cin >> S[i];
        int len = S[i].size();
        // Lưu độ dài khác nhau
        if(H[len].empty()) lengths.push_back(len);

        // Tính hash của xâu S[i]
        ll h = 0;
        for(char c : S[i]) h = (h * BASE + (c-'a'+1)) % MOD;
        H[len].insert(h);
    }

    cin >> T;
    T = "#" + T;  // 1-based indexing
    int L = T.size() - 1;

    // Precompute POW
    POW[0] = 1;
    for(int i = 1; i <= L; i++) POW[i] = POW[i-1] * BASE % MOD;

    // Precompute hash prefix của T
    hashT[0] = 0;
    for(int i = 1; i <= L; i++) hashT[i] = (hashT[i-1] * BASE + (T[i]-'a'+1)) % MOD;

    // DP
    countT[0] = 1; // rỗng có 1 cách
    for(int i = 1; i <= L; i++){
        for(int len : lengths){
            if(i - len + 1 >= 1){
                ll h = get_hash(i - len + 1, i);
                if(H[len].count(h)) countT[i] = (countT[i] + countT[i - len]) % MOD;
            }
        }
    }

    cout << countT[L];
}
