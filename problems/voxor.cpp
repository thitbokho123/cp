#include <bits/stdc++.h>
using namespace std;

#define int long long

const int NUMBEROFNODES = 500005;
const int LG = 20;

struct Trie {
    struct Node {
        int child[2];
        int cnt, exist;
    } nodes[NUMBEROFNODES];

    int cur;
    Trie() : cur(0) {
        memset(nodes[0].child, -1, sizeof(nodes[0].child));
        nodes[0].cnt = nodes[0].exist = 0;
    }

    int new_node() {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].cnt = nodes[cur].exist = 0;
        return cur;
    }

    void add_number(int x) {
        int pos = 0;
        for (int i = LG; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (nodes[pos].child[b] == -1) {
                nodes[pos].child[b] = new_node();
            } 
            pos = nodes[pos].child[b];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
    }
    //tim so thu k
    //moi so deu duoc xor voi cur_xor
    //
    int query(int cur_xor, int k) {
        int res = 0;
        int pos = 0;
        for (int i = LG; i >= 0; i--) {
            int c = (cur_xor >> i) & 1;

            for (int j = 1; j >= 0; j--) {
                int bit = j ^ c; 
                int nxt = nodes[pos].child[bit];
                if (nxt == -1) continue;
                if (nodes[nxt].cnt >= k) {
                    res |= (j << i);
                    pos = nxt;
                    break;
                } else {
                    k -= nodes[nxt].cnt; 
                }
            }
        }
        return res;
    }

};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    int a[n];
    Trie trie;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        trie.add_number(a[i]);
    }
    int cur_xor = 0;
    string type;
    int x;
    while (q--) {
        cin >> type >> x;
        if (type == "XOR") {
            cur_xor ^= x;
        } else {
            cout << trie.query(cur_xor, x) << '\n';
        }
    }
}
