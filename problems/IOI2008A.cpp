#include<bits/stdc++.h>
using namespace std;

const int NUMBEROFNODES = 500005;
string longest = "";
int branch, posBranch;
vector<char> ans;

vector<bool> isMarked(NUMBEROFNODES, false);

struct Trie {
    struct Node {
        int child[26];
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

    void dfs(int pos, string& current_string) {
        if (nodes[pos].exist) ans.push_back('P');

        int special_child = -1;

        if (isMarked[pos]) {
            int depth = current_string.size();
            if (depth < longest.size()) {
                int c = longest[depth] - 'a';
                if (nodes[pos].child[c] != -1) {
                    special_child = nodes[pos].child[c];
                }
            }
        }

        for (int i = 0; i < 26; i++) {
            if (nodes[pos].child[i] != -1 && nodes[pos].child[i] != special_child) {
                current_string += char(i + 'a');
                ans.push_back(char(i + 'a'));
                dfs(nodes[pos].child[i], current_string);
                current_string.pop_back();
                ans.push_back('-');
            }
        }
        
        if (special_child != -1) {
            char c = longest[current_string.size()];
            current_string += c;
            ans.push_back(c);
            dfs(special_child, current_string);
        }
    }
};

void markLongest(Trie &trie, string &longest) {
    int pos = 0;
    isMarked[pos] = true;
    for (auto f : longest) {
        int c = f - 'a';
        pos = trie.nodes[pos].child[c];
        isMarked[pos] = true;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    Trie trie;
    string s;
    int mxLen = 0;
    for (int i = 0; i < n; i++) {
        cin >> s;
        trie.add_string(s);
        if (s.length() > mxLen) {
            longest = s;
            mxLen = s.length();
        }
    }
    markLongest(trie, longest);
    string current_string = "";
    trie.dfs(0, current_string);
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << '\n';
    }
}