#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

string s, t;
int n;
vector<string> path;

void dfs(int i, int j, stack<char> st) {
    if (i == n && j == n) {
        for (int k = 0; k < path.size(); ++k) {
            if (k > 0) cout << " ";
            cout << path[k];
        }
        cout << "\n";
        return;
    }

    if (i < n) {
        st.push(s[i]);
        path.push_back("i");
        dfs(i + 1, j, st);
        path.pop_back();
        st.pop();
    }

    if (!st.empty() && j < n && st.top() == t[j]) {
        char c = st.top(); st.pop();
        path.push_back("o");
        dfs(i, j + 1, st);
        path.pop_back();
        st.push(c);
    }
}

int main() {
    while (cin >> s >> t) {
        cout << "[\n";
        if (s.length() == t.length()) {
            n = s.length();
            path.clear();
            stack<char> st;
            dfs(0, 0, st);
        }
        cout << "]\n";
    }
    return 0;
}
