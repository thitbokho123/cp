#include<bits/stdc++.h>
using namespace std;

int n;
int a[30];
vector<int> v1, v2;
//idea: chia doi tap thanh cac tap kieu 1 n-1 2 n-2... dan dan
//tinh tong tap 1 r chat nhi phan tap 2 thoi
//dpt bnh nhi

void backtrack(int i, vector<int> v) {
    if (i == 0) {
        
        return;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        
    }
}