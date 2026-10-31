#include<bits/stdc++.h>
using namespace std;

const int NUMBEROFNODES = 500005;
int l, k;
bool flag = false;
map<pair<int,int>, int> freq;

struct Trie {
    struct Node {
        int child[26];
        int cnt, exist;
        int idx;
    } nodes[NUMBEROFNODES];

    int cur;
    Trie() : cur(0) {
        memset(nodes[0].child, -1, sizeof(nodes[0].child));
        nodes[0].cnt = nodes[0].exist = nodes[0]. idx = 0;
    }

    int new_node(int depth) {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].cnt = nodes[cur].exist = 0;
        nodes[cur].idx = depth;
        return cur;
    }

    void add_string(string s) {
        int pos = 0;
        int suf = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) {
                nodes[pos].child[c] = new_node(nodes[pos].idx + 1);
            }
            pos = nodes[pos].child[c];
            if (nodes[pos].cnt > 0) {
                freq[{nodes[pos].idx, nodes[pos].cnt}]--;
            }
            nodes[pos].cnt++;
            freq[{nodes[pos].idx, nodes[pos].cnt}]++;
        }
        nodes[pos].exist++;
    }

    bool delete_string_recursive(int pos, string &s, int i) {
        if (i != s.size()) {
            int c = s[i] - 'a';
            bool isChildDeleted = delete_string_recursive(nodes[pos].child[c], s, i + 1);
            if (isChildDeleted) nodes[pos].child[c] = -1;
        } else {
            nodes[pos].exist--;
        }
        if (pos) {
            if (nodes[pos].cnt > 0) {
                freq[{nodes[pos].idx, nodes[pos].cnt}]--;
            }
            nodes[pos].cnt--;
            if (nodes[pos].cnt > 0) {
                freq[{nodes[pos].idx, nodes[pos].cnt}]++;
            }
            if (nodes[pos].cnt == 0 && nodes[pos].exist == 0) return true;
        }
        return false;
    }

    void delete_string(string s) {
        if (find_string(s) == false) return;
        delete_string_recursive(0, s, 0);
    }

    bool find_string(string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) {
                return false;
            }
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }

    void query() {
        if (freq[{l, k}] > 0) cout << "YES\n";
        else cout << "NO\n";    
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    Trie trie;
    map<int, string> mp;
    for (int i = 1; i <= q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            string s;
            cin >> s;
            reverse(s.begin(), s.end());
            mp[i] = s;
            trie.add_string(s);
        } else if (type == 2) {
            cin >> k >> l;
            trie.query();
        } else {
            int x;
            cin >> x;
            trie.delete_string(mp[x]);
        }
    }
}