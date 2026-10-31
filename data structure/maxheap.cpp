#include <bits/stdc++.h>
using namespace std;

int heap[1000];
int sz = 0;

void swimUp(int idx) {
    while (((idx - 1) / 2 >= 0) && idx) {
        if (heap[idx] > heap[(idx - 1) / 2]) {
            swap(heap[idx], heap[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        } else {
            break;
        }
    }
}

void insert(int num) {
    heap[sz] = num;
    swimUp(sz);
    sz++;
}

void sinkDown() {
    int idx = 0;

    while (idx * 2 + 1 < sz) {
        if (heap[idx] < heap[idx * 2 + 1]) {
            swap(heap[idx], heap[(idx * 2) + 1]);
            idx = idx * 2 + 1;
        } else if ((heap[idx] < heap[(idx * 2) + 2]) && (idx * 2 + 2 <= sz)) {
            swap(heap[idx], heap[(idx * 2) + 2]);
            idx = idx * 2 + 2;
        } else {
            break;
        }
    }
}

void removeMax() {
    swap(heap[sz - 1], heap[0]);
    sz--;
    sinkDown();
}

void print() {
    for (int i = 0; i < sz; i++) {
        cout << heap[i] << ' ';
    }
    cout << '\n';
}

int main() {
    insert(5);
    insert(4);
    insert(1);
    insert(6);
    insert(3);
    insert(2);
    print();
    removeMax();
    print();
}