#include<bits/stdc++.h>
using namespace std;

const int NUMBEROFNODES = 5000005;
bool flag = false;

struct Trie {
    struct Node {
        int child[26];
        int cnt, exist;
        vector<int> idx;
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

    void add_string(string s, int id) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) {
                nodes[pos].child[c] = new_node();
            }
            pos = nodes[pos].child[c];
            nodes[pos].cnt++;
        }
        nodes[pos].exist++;
        auto it = lower_bound(nodes[pos].idx.begin(), nodes[pos].idx.end(), id);
        nodes[pos].idx.insert(it, id);
    }

    bool delete_string_recursive(int pos, string& s, int i, int id) {
        if (i != s.size()) {
            int c = s[i] - 'a';
            bool isChildDeleted = delete_string_recursive(nodes[pos].child[c], s, i + 1, id);
            if (isChildDeleted) nodes[pos].child[c] = -1;
        } else {
            nodes[pos].exist--;
            auto it = lower_bound(nodes[pos].idx.begin(), nodes[pos].idx.end(), id);
            if (it != nodes[pos].idx.end() && *it == id) {
                nodes[pos].idx.erase(it);
            }
        }
        if (pos) {
            nodes[pos].cnt--;
            if (nodes[pos].cnt == 0) return true;
        }
        return false;
    }

    void delete_string(string s, int id) {
        if (find_string(s) == false) return;
        delete_string_recursive(0, s, 0, id);
    }

    bool find_string(string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }

    bool query2(string s, int l, int r) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
            if (nodes[pos].exist) {
                auto it = lower_bound(nodes[pos].idx.begin(), nodes[pos].idx.end(), l);
                if (it != nodes[pos].idx.end() && *it <= r) return true;
            }
        }
        return false;
    }

    bool query3(string s, int l, int r) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        dfs(pos, l, r);
        if (flag) return true;
        else return false;
    }

    void dfs(int pos, int l, int r) {
        if (nodes[pos].exist) {
            auto it = lower_bound(nodes[pos].idx.begin(), nodes[pos].idx.end(), l);
            if (it != nodes[pos].idx.end() && *it <= r) flag = true;
            return;
        }
        for (int i = 0; i < 26; i++) {
            if (nodes[pos].child[i] != -1) {
                dfs(nodes[pos].child[i], l, r);
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    Trie trie;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        trie.add_string(s[i], i);
    }
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int i;
            string k;
            cin >> i >> k;
            trie.delete_string(s[i], i);
            s[i] = k;
            trie.add_string(s[i], i);
        } else if (type == 2) {
            int l, r;
            string st;
            cin >> l >> r >> st;
            if(trie.query2(st, l, r)) cout <<"Y\n";
            else cout << "N\n";
        } else {
            int l, r;
            string st;
            cin >> l >> r >> st;
            flag = false;
            if(trie.query3(st, l, r)) cout <<"Y\n";
            else cout << "N\n";
        }
    }
}