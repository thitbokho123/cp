#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = min(r - i, p[l + (r - i)]);
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for (auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        string r = s;
        reverse(r.begin(), r.end());
        int pos = 0;
        while (s[pos] == r[pos] && pos < s.length() / 2) {
            pos++;
        }
        string man = s.substr(pos, s.length() - 2 * pos);
        for (int i = 0; i < pos; i++) {
            cout << s[i];
        }
        if(man.size()) {
            vector<int> pOdd = manacher_odd(man);
            vector<int> pEven = manacher(man);

            int maxLen = 0;
            int center = 0;
            bool isOdd = false;

            // Tìm palindrome có độ dài lẻ lớn nhất
            for (int i = 0; i < pOdd.size(); i++) {
                int len = 2 * (pOdd[i] - 1) + 1;
                if (len > maxLen && (i - pOdd[i] + 1 == 0 || i + pOdd[i] - 1 == pOdd.size() - 1)) {
                    maxLen = len;
                    center = i;
                    isOdd = true;
                }
            }

            // Tìm palindrome có độ dài chẵn lớn nhất
            for (int i = 0; i < pEven.size(); i++) {
                int len = (pEven[i] - 1);
                if (len > maxLen && (i - pEven[i] + 1 == -1 || i + pEven[i] - 2 == pEven.size() - 1)) {
                    maxLen = len;
                    center = i;
                    isOdd = false;
                }
            }

        
            string longestPalindrome = "";
            if (isOdd) {
                int radius = (maxLen - 1) / 2;
                longestPalindrome = man.substr(center - radius, maxLen);
            } else {
                int len = maxLen;
                int original_center = (center - 1) / 2;
                longestPalindrome = man.substr(original_center - len/2 + 1, len);
            }

            cout << longestPalindrome;
        }

        for (int j = pos - 1; j >= 0; j--) {
            cout << s[j];
        }
        cout << '\n';

    }
}