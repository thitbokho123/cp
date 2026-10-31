#include <bits/stdc++.h>
using namespace std;

int heap[1000];
int sz = 0;

void swimUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[idx] < heap[parent]) {
            swap(heap[idx], heap[parent]);
            idx = parent;
        } else break;
    }
}

void insert(int val) {
    heap[sz] = val;
    swimUp(sz);
    sz++;
}

void sinkDown() {
    int idx = 0;
    while (idx * 2 + 1 < sz) {
        int left = idx * 2 + 1;
        int right = idx * 2 + 2;
        int smallest = left;

        if (right < sz && heap[right] < heap[left]) {
            smallest = right;
        }

        if (heap[idx] > heap[smallest]) {
            swap(heap[idx], heap[smallest]);
            idx = smallest;
        } else break;
    }
}

void removeMin() {
    swap(heap[0], heap[sz - 1]);
    sz--;
    sinkDown();
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        insert(x);
    }
    for (int i = 0; i < n; i++) {
        cout << heap[0] << ' ';
        removeMin();
    }
}
