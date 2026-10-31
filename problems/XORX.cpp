#include <bits/stdc++.h>
using namespace std;

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

    int query(int x) {
        int res = 0;
        int pos = 0;
        for (int i = LG; i >= 0; i--) {
            int c = (x >> i) & 1;
            if (nodes[pos].child[c ^ 1] != -1) {
                res += (1LL << i);
                pos = nodes[pos].child[c ^ 1];
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
        int ans = 0, mx = 0;
        int n, K;
        cin >> n >> K;
        int a[n];
        for (int i = 0; i < n; i++) cin >> a[i];

        Trie trie;
        trie.add_number(0); // prefix empty

        int pref = 0;
        for (int i = 0; i < n; i++) {
            pref ^= a[i];   
            trie.add_number(pref);    
            if (trie.query(K) > mx) {
                mx = trie.query(K);
                ans = mx ^ K;
            }          
        }
        cout << ans << '\n';
    }
}