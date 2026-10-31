#include <bits/stdc++.h>
using namespace std;

int quick(int lo, int hi, int a[]) {
    int p = a[hi];
    int i = lo - 1;
    for (int j = lo; j <= hi - 1; j++) {
        if (a[j] <= p) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[hi]);
    return (i + 1);
}

void quicksort(int lo, int hi, int a[]) {
    if (lo < hi) {
        int p = quick(lo, hi, a);
        quicksort(lo, p - 1, a);
        quicksort(p + 1, hi, a);
    }

}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    quicksort(0, n, a);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
}