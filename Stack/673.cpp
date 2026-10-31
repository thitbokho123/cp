#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    string s;
    cin.ignore();

    while (t--) {
        getline(cin,s);
        stack<char>st;
        bool flag = false;

        for (int i = 0; i < s.length(); i++) {
            if ((s[i] == '(') || (s[i] == '[')) {
                st.push(s[i]);
            } else if (s[i] == ')') {
                if ( (st.empty()) || (st.top() != '(')){
                    flag = true;
                    break;
                } else {
                    st.pop();
                }
            } else {
                if ((st.empty()) || (st.top() != '[')) {
                    flag = true;
                    break;
                } else {
                    st.pop();
                }
            }
        }

        if ((!flag) && (st.empty())) {
            cout<<"Yes";
        } else {
            cout<<"No";
        }
        cout<<'\n';
    }
}