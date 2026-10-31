#include<bits/stdc++.h>
using namespace std;

const int MAXN = 250001;
int n, block_size, m;
int a[MAXN];
vector<vector<int>> blocks;
long long total_inversions = 0;

void build() {
    block_size = sqrt(n);
    if (block_size == 0) block_size = 1;
    blocks.resize((n + block_size - 1) / block_size);
    for (int i = 0; i < n; i++) {
        blocks[i / block_size].push_back(a[i]);
    }
    for (auto &block : blocks) {
        sort(block.begin(), block.end());
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                total_inversions++;
            }
        }
    }
}

int get_inversions_within_block(int pos, int val) {
    int block_idx = pos / block_size;
    int inversions = 0;
    for (int i = block_idx * block_size; i < min(n, (block_idx + 1) * block_size); i++) {
        if (i < pos && a[i] > val) {
            inversions++;
        } else if (i > pos && a[i] < val) {
            inversions++;
        }
    }
    return inversions;
}

int get_inversions_across_blocks(int pos, int val) {
    int block_idx = pos / block_size;
    int inversions = 0;
    for (int i = 0; i < block_idx; i++) {
        auto it = upper_bound(blocks[i].begin(), blocks[i].end(), val);
        inversions += (blocks[i].end() - it);
    }
    for (int i = block_idx + 1; i < (int)blocks.size(); i++) {
        auto it = lower_bound(blocks[i].begin(), blocks[i].end(), val);
        inversions += (it - blocks[i].begin());
    }
    return inversions;
}

void update(int x, int y) {
    int pos = x - 1;
    int old_val = a[pos];
    int block_idx = pos / block_size;
    
    total_inversions -= get_inversions_within_block(pos, old_val);
    total_inversions -= get_inversions_across_blocks(pos, old_val);
    
    a[pos] = y;
    auto &block = blocks[block_idx];
    block.erase(lower_bound(block.begin(), block.end(), old_val));
    block.insert(lower_bound(block.begin(), block.end(), y), y);
    
    total_inversions += get_inversions_within_block(pos, y);
    total_inversions += get_inversions_across_blocks(pos, y);

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

    cin >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        update(x, y);
    }
    
}