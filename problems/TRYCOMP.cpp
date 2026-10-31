#include<bits/stdc++.h>
using namespace std;

const int NUMBEROFNODES = 2000005;

struct Trie {
    struct Node {
        int child[26];
        int exist, cnt;
        int best_length;
        int best_word;
    } nodes[NUMBEROFNODES];

    vector<string> words;
    int cur;
    Trie() : cur(0) {
        memset(nodes[0].child, -1, sizeof(nodes[0].child));
        nodes[0].exist = nodes[0].cnt = 0;
        nodes[0].best_length = 0;
        nodes[0].best_word = -1;
    }

    int new_node() {
        cur++;
        memset(nodes[cur].child, -1, sizeof(nodes[cur].child));
        nodes[cur].exist = nodes[cur].cnt = 0;
        nodes[cur].best_length = 0;
        nodes[cur].best_word = -1;
        return cur;
    }

    void add_string(string s) {
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
        int x = nodes[pos].exist;
        pos = 0;
        int id = words.size();
        words.push_back(s);
        for (auto f : s) {
            int c = f - 'a';
            pos = nodes[pos].child[c];
            if (nodes[pos].best_length < x) {
                nodes[pos].best_length = x;
                nodes[pos].best_word = id;
            } else if (nodes[pos].best_length == x) {
                if (words[nodes[pos].best_word] > s) {
                    nodes[pos].best_word = id;
                }
            }
        }
    }

    bool delete_string_recursive(int pos, string& s, int i) {
        if (i != s.size()) {
            int c = s[i] - 'a';
            bool isChildDeleted = delete_string_recursive(nodes[pos].child[c], s, i + 1);
            if (isChildDeleted) nodes[pos].child[c] = -1;
        } else {
            nodes[pos].exist--;
        }
        if (pos) {
            nodes[pos].cnt--;
            if (nodes[pos].cnt == 0) return true;
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
            if (nodes[pos].child[c] == -1) return false;
            pos = nodes[pos].child[c];
        }
        return (nodes[pos].exist != 0);
    }

    void query(string s) {
        int pos = 0;
        for (auto f : s) {
            int c = f - 'a';
            if (nodes[pos].child[c] == -1) {
                cout << -1 << '\n';
                return;
            }
            pos = nodes[pos].child[c];
        }
        cout << words[nodes[pos].best_word] << ' ' << nodes[pos].best_length << '\n';
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Trie trie;
    string s;
    while (n--) {
        cin >> s;
        trie.add_string(s);
    }
    int q;
    cin >> q;
    while (q--) {
        cin >> s;
        trie.query(s);
    }
}