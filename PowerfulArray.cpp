#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAX_VAL = 1000005; 
int BLOCK_SIZE; 

struct Query {
    int l, r, id;
    
    bool operator<(const Query& other) const {
        int block_a = l / BLOCK_SIZE;
        int block_b = other.l / BLOCK_SIZE;
        if (block_a != block_b)
            return block_a < block_b;
        
        return (block_a % 2 == 0) ? (r < other.r) : (r > other.r);
    }
} queries[MAXN];

int n, t;
int a[MAXN];
long long cnt[MAX_VAL]; 
long long current_answer = 0; 
long long answers[MAXN]; 


void add(int index) {
    int val = a[index];
    long long k = cnt[val];
    
    current_answer -= (k * k * val);
    
    cnt[val]++;
    
    k = cnt[val];
    current_answer += (k * k * val);
}

void remove(int index) {
    int val = a[index];
    long long k = cnt[val];
    
    current_answer -= (k * k * val);
    
    cnt[val]--;
    
    k = cnt[val];
    current_answer += (k * k * val);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    if (!(cin >> n >> t)) return 0;

    BLOCK_SIZE = sqrt(n); 

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < t; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries, queries + t);

    int L = 1;
    int R = 0;

    for (int i = 0; i < t; i++) {
        int q_l = queries[i].l;
        int q_r = queries[i].r;

        while (L > q_l) add(--L);
        while (R < q_r) add(++R);
        while (L < q_l) remove(L++);
        while (R > q_r) remove(R--);

        answers[queries[i].id] = current_answer;
    }

    for (int i = 0; i < t; i++) {
        cout << answers[i] << "\n";
    }

    return 0;
}