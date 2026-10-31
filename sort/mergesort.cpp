#include <bits/stdc++.h>
using namespace std;

void merge(int lo, int hi, int mi, int arr[]) {
    int x = mi - lo + 1;
    int y = hi - mi;

    int b[x], c[y];
    for (int i = 0; i < x; i++) {
        b[i] = arr[lo + i];
    }
    for (int j = 0; j < y; j++) {
        c[j] = arr[mi + j + 1];
    }

    int i = 0, j = 0, k = lo;

    while (i < x && j < y) {
        if (b[i] <= c[j]) {
            arr[k] = b[i];
            i++;
            k++;
        } else {
            arr[k] = c[j];
            j++;
            k++;
        }
    }

    while (i < x) {
        arr[k] = b[i];
        i++;
        k++;
    }

    while (j < y) {
        arr[k] = c[j];
        j++;
        k++;
    }

}

void mergesort(int lo, int hi, int arr[]) {
    int mi = lo + (hi - lo) / 2;
    if (lo < hi) {
        mergesort(lo, mi, arr);
        mergesort(mi + 1, hi, arr);
        merge(lo, hi, mi, arr);
    }
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    mergesort(0, n - 1, a);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
}