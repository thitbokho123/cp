#include <bits/stdc++.h>
using namespace std;
#define sp ' '
#define endl '\n'
 
const int BLOCK_SIZE = 800;
const int N = 2e5 + 5;
const int LIM = 100;
int n, nblocks;
int a[N];
int lazy[N / BLOCK_SIZE + 1][LIM + 1];
 
void doLazy(int id) { // L R là đầu trái và đầu phải của phần dư bên trái
    int L = id * BLOCK_SIZE;
    int R = min(n - 1, (id + 1) * BLOCK_SIZE - 1);
    for (int i = L; i <= R; i++) {
        a[i] = lazy[id][a[i]]; // thay đổi giá trị các phần tử bằng mảng lazy
    }
    for (int i = 1; i <= 100; i++) {
        lazy[id][i] = i; // đã cập nhật xong, reset lại mảng lazy về ban đầu
    }
}
 
void manualUpdate(int L, int R, int oval, int nval) { // L R là đầu trái và đầu phải của phần dư bên trái
    int id = R / BLOCK_SIZE;
    doLazy(id);
    for (int i = L; i <= R; i++) {
        if (a[i] == oval) {
            a[i] = nval;
        }
    }
}
 
void blockUpdate(int id, int oval, int nval) {
    for (int i = 1; i <= LIM; i++) {
        if (lazy[id][i] == oval) {
            lazy[id][i] = nval;
        }
    }
}
 
void update(int l, int r, int oval, int nval) {
    int blockL = l / BLOCK_SIZE, blockR = r / BLOCK_SIZE;
    if (blockL == blockR) {
        manualUpdate(l, r, oval, nval);
        return;
    }
    for (int i = blockL + 1; i < blockR; ++i) {
        blockUpdate(i, oval, nval);
    }
    manualUpdate(l, (blockL + 1) * BLOCK_SIZE - 1, oval, nval);
    manualUpdate(blockR * BLOCK_SIZE, r, oval, nval);
}
 
void init() {
    nblocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < nblocks; i++) {
        for (int j = 1; j <= 100; j++) {
            lazy[i][j] = j;
        }
    }
}
 
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    init();
    int q; cin >> q;
    for (int Q = 0; Q < q; Q++) {
        int l, r, oval, nval;
        cin >> l >> r >> oval >> nval;
        l--; r--;
        update(l, r, oval, nval);
    }
    for (int i = 0; i < nblocks; i++) {
        doLazy(i);
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << sp;
    }
    cout << endl;
}
