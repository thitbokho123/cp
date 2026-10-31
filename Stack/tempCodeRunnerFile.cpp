#include <bits/stdc++.h>
using namespace std;

vector <int> adj[10000001];


int main() {
    string k;
    while (getline(cin, k)) {
        string s = k;
        int i = 0;
        int num = 0;
        vector <int> v;
        bool neg = false;
        while (true) {
            if (i == s.length()) {
                break;
            }
            if (s[i] == '-') {
                neg = true;
            }
            if ((s[i] != ' ') && (s[i] != '-')) {
                num *= 10;
                if (!neg) {
                    num += s[i] - '0';
                } else {
                    num += -(s[i] - '0');
                }

            } else if (s[i] == ' '){
                v.push_back(num);
                num = 0;
                neg = false;
            }
            i++;
        }

        v.push_back(num);

        stack <int> st;
        bool flag = true;
        map <int, int> mp;

        for (int i = 0; i < v.size(); i++) {
            if (v[i] < 0) {
                st.push(v[i]);
                mp[v[i]] = 0;
            } else {
                if (st.empty()) {
                    cout<<3<<' '<<v[i]<<'\n';
                    flag = false;
                    break;
                }
                if (st.top() != -v[i]) {
                    flag = false;
                    break;
                } else {
                    int x = st.top();
                    st.pop();
                    if (st.size()) {
                        mp[st.top()] += abs(x);
                        if (mp[st.top()] > abs(st.top())) {
                            flag = false;
                            break;
                        }
                    }
                }
            }
        }

        if (flag) {
            cout << ":-) Matrioshka!\n";
        } else {
            cout << ":-( Try again.\n";
        }
    }
}