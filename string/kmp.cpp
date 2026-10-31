#include <bits/stdc++.h>
using namespace std;

int main() {
    string text, pattern;
    cin >> text >> pattern;

    vector <int> pi(pattern.length());

    pi[0] = 0;

    int j = 0;
    
    for (int i = 1; i < pattern.length(); i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        pi[i] = j;
    }

    j = 0;

    for (int i = 0; i < text.length(); i++) {
        while (j > 0 && pattern[j] != text[i]) {
            j = pi[j - 1];
        }
        if (pattern[j] == text[i]) {
            j++;
        }
        if (j == pattern.length()) {
            cout << "YES";
            return 0;
        }
    }

    cout << "NO";
}