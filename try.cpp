#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  int n;
  cin >> n;
  int k = 0;
  if (n) cout << 0 << '\n';
  for (int i = 2; i <= n; i++) {
    int x = i * i;
    cout << x * (x - 1) / 2 - k * 8 << '\n';
    k += i - 1;
  }
}