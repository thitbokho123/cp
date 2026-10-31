#include <bits/stdc++.h>
using namespace std;

int main() {
    string text, pattern;
    cin >> text >> pattern;
    text = pattern + "$" + text;
    vector <int> z (text.length(), 0);

    int l = 0, r = 0;
    for (int i = 1; i < text.length(); i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < text.length() && text[z[i]] == text[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    for (int i = 0; i < text.length(); i++) {
        if (z[i] == pattern.length()) {
            cout << i - pattern.length() << ' ';
        }
    }
}