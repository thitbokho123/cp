#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250001;
int n, m;
int a[MAXN];
vector<int> blocks[501]; /
int block_size;
long long total_inversions = 0;

long long count_inversions_for_value(int pos, int val, int direction) {
    long long count = 0;
    int block_idx = pos / block_size;

    for (int i = block_idx * block_size; i < min(n, (block_idx + 1) * block_size); i++) {
        if (direction == 1) { 
            if (i < pos && a[i] > val) {
                count++;
            }
        } else { 
            if (i > pos && a[i] < val) {
                count++;
            }
        }
    }

    if (direction == 1) { 
        for (int i = 0; i < block_idx; i++) {
            auto it = upper_bound(blocks[i].begin(), blocks[i].end(), val);
            count += blocks[i].end() - it;
        }
    } else { 
        for (int i = block_idx + 1; i < (n + block_size - 1) / block_size; i++) {
            auto it = lower_bound(blocks[i].begin(), blocks[i].end(), val);
            count += it - blocks[i].begin();
        }
    }

    return count;
}

void build() {
    block_size = static_cast<int>(sqrt(n));
    if (block_size == 0) block_size = 1;

    for (int i = 0; i < n; i++) {
        blocks[i / block_size].push_back(a[i]);
    }
    for (int i = 0; i < (n + block_size - 1) / block_size; i++) {
        sort(blocks[i].begin(), blocks[i].end());
    }
}

void update(int x, int y) {
    int pos = x - 1;
    int old_val = a[pos];
    int block_idx = pos / block_size;
    
    total_inversions -= count_inversions_for_value(pos, old_val, 1);
    total_inversions -= count_inversions_for_value(pos, old_val, 0);

    a[pos] = y;

    auto& block = blocks[block_idx];
    block.erase(lower_bound(block.begin(), block.end(), old_val));
    block.insert(lower_bound(block.begin(), block.end(), y), y);

    total_inversions += count_inversions_for_value(pos, y, 1);
    total_inversions += count_inversions_for_value(pos, y, 0);

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
        total_inversions += count_inversions_for_value(i, a[i], 0);
    }

    cin >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        update(x, y);
    }
}
