#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = min(r - i, p[l + (r - i)]);
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
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
    string s;
    cin >> s;

    vector<int> pOdd = manacher_odd(s);
    vector<int> pEven = manacher(s);

    int maxLen = 0;
    int center = 0;
    bool isOdd = false;

    // Tìm palindrome có độ dài lẻ lớn nhất
    for (int i = 0; i < pOdd.size(); i++) {
        int len = 2 * (pOdd[i] - 1) + 1;
        if (len > maxLen) {
            maxLen = len;
            center = i;
            isOdd = true;
        }
    }

    // Tìm palindrome có độ dài chẵn lớn nhất
    for (int i = 0; i < pEven.size(); i++) {
        int len = (pEven[i] - 1);
        if (len > maxLen) {
            maxLen = len;
            center = i;
            isOdd = false;
        }
    }

    string longestPalindrome = "";
    if (isOdd) {
        int radius = (maxLen - 1) / 2;
        longestPalindrome = s.substr(center - radius, maxLen);
    } else {
        int len = maxLen;
        int original_center = (center - 1) / 2;
        longestPalindrome = s.substr(original_center - len/2 + 1, len);
    }

    cout << longestPalindrome << endl;

    return 0;
}