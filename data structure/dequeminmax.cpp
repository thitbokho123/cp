#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    deque<int> dq;
    vector<int> minRange;

    for (int i = 0; i < n; i++) {
        // Xóa phần tử không còn trong cửa sổ
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();

        // Duy trì dq tăng dần
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        dq.push_back(i);

        // Kết quả khi đủ k phần tử
        if (i >= k - 1) minRange.push_back(a[dq.front()]);
    }

    // In kết quả
    for (int x : minRange) cout << x << " ";
    cout << "\n";
}