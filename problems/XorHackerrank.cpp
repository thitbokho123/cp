#include<bits/stdc++.h>
using namespace std;

const int NUMBEROFNODES = 500005;
const int LG = 20;

struct Trie {
    struct Node {
        int child[2];
        int cnt, exist;
        set<int> idx;
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

    void add_number(int x, int idx) {
        int pos = 0;
        for (int i = LG; i >= 0; i--) {
            int c = (x >> i) & 1;
            if (nodes[pos].child[c] == -1) {
                nodes[pos].child[c] = new_node();
            }
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
            nodes[pos].idx.insert(idx);
        }
        nodes[pos].exist++;
    }

    int query(int l, int r, int k) {
        int pos = 0;
        int res = 0;
        for (int i = LG; i >= 0; i--) {
            int c = (k >> i) & 1;
            if (nodes[pos].child[c ^ 1] != -1) {
                auto it = nodes[pos].idx.upper_bound(l);
                if (*it <= r) {
                    res += (1LL << i);
                    pos = nodes[pos].child[c ^ 1];
                } else {
                    pos = nodes[pos].child[c];
                }
            } else {
                pos = nodes[pos].child[c];
            }
        }
        return res;
    }
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        Trie trie;
        int n, q;
        cin >> n >> q;
        int a[n + 1];
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            trie.add_number(a[i], i);
        }
        while (q--) {
            int l, r, k;
            cin >> l >> r >> k;
            cout << trie.query(l, r, k) << '\n';
        }
    }
}