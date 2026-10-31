#include <bits/stdc++.h>
using namespace std;

#define int long long

const int NUMBEROFNODES = 500005;
const int LG = 20;
struct Trie{
    struct Node{
        int child[2];
        int exist, cnt;
    } nodes[NUMBEROFNODES];

    int cur;
    Trie() : cur(0) {
        memset(nodes[0].child, -1, sizeof(nodes[cur].child));
        nodes[0].exist = nodes[0].cnt = 0;
    };

    int new_node() {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        return cur;
    }

    void add_number(int x) {
        int pos = 0;
        for (int i = LG; i >= 0; i--) {
            int c = (x >> i) & 1;
            if (nodes[pos].child[c] == -1) nodes[pos].child[c] = new_node();
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }

    int query(int x, int k) {
        int res = 0;
        int pos = 0;
        for (int i = LG; i >= 0; i--) {
            if (pos == -1) break;
            int xb = (x >> i) & 1;
            int kb = (k >> i) & 1;
            if (kb == 1) {
                if (nodes[pos].child[xb] != -1) {
                    res += nodes[nodes[pos].child[xb]].cnt;
                }
                pos = nodes[pos].child[xb ^ 1];
            } else {
                pos = nodes[pos].child[xb];
            }
        }
        return res;
    }

};

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int ans = 0;
        int n, K;
        cin >> n >> K;
        int a[n];
        for (int i = 0; i < n; i++) cin >> a[i];

        Trie trie;
        trie.add_number(0); // prefix empty

        int pref = 0;
        for (int i = 0; i < n; i++) {
            pref ^= a[i];                // tính prefix XOR
            ans += trie.query(pref, K);  // đếm số prefix trước đó tạo subarray XOR < K
            trie.add_number(pref);       // thêm prefix hiện tại vào trie
        }
        cout << ans << '\n';
    }
}
