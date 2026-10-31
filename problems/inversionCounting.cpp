#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250001;
int n, m;
int a[MAXN];
multiset<int> blocks[501]; 
int block_size;
long long total_inversions = 0;

long long count_inversions_in_block(int block_idx, int val, int direction) {
    if (direction == 1) { 
        auto it = blocks[block_idx].upper_bound(val);
        return distance(it, blocks[block_idx].end());
    } else { 
        auto it = blocks[block_idx].lower_bound(val);
        return distance(blocks[block_idx].begin(), it);
    }
}

long long count_inversions_for_value(int pos, int val) {
    long long count = 0;
    int block_idx = pos / block_size;

    for (int i = block_idx * block_size; i < min(n, (block_idx + 1) * block_size); i++) {
        if (i < pos && a[i] > val) {
            count++;
        }
        if (i > pos && a[i] < val) {
            count++;
        }
    }

    for (int i = 0; i < block_idx; i++) {
        count += count_inversions_in_block(i, val, 1);
    }
    for (int i = block_idx + 1; i < (n + block_size - 1) / block_size; i++) {
        count += count_inversions_in_block(i, val, 0);
    }

    return count;
}

void build() {
    block_size = static_cast<int>(sqrt(n));
    if (block_size == 0) block_size = 1;

    for (int i = 0; i < n; i++) {
        blocks[i / block_size].insert(a[i]);
    }
}

void update(int x, int y) {
    int pos = x - 1;
    int old_val = a[pos];
    int block_idx = pos / block_size;
    
    total_inversions -= count_inversions_for_value(pos, old_val);
    
    a[pos] = y;

    blocks[block_idx].erase(blocks[block_idx].find(old_val));
    blocks[block_idx].insert(y);

    total_inversions += count_inversions_for_value(pos, y);

    cout << total_inversions << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    build();

    for (int i = 0; i < n; i++) {
        total_inversions += count_inversions_for_value(i, a[i]);
    }

    cin >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        update(x, y);
    }
    
}
