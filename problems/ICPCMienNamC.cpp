#include <bits/stdc++.h>
using namespace std;

struct Oxyz {
    int x, y, z;
    bool operator<(const Oxyz &other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<Oxyz> v;
    int ans = n * k;
    for (int i = 1; i <= k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        v.push_back({x, y, z});
    }
    map<Oxyz,bool> mp;
    for (int i = 0; i < k - 1; i++) {
        for (int j = i + 1; j < k; j++) {
            if (v[i].x == v[j].x && v[i].y == v[j].y && v[i].z == v[j].z) {
                ans -= n;
                continue;
            }
            if (v[i].x != 0 && v[i].x == v[j].x && v[i].y != v[j].y && v[i].z != v[j].z && mp[{v[i].x, v[i].y + v[j].y, v[i].z + v[j].z}] == false) {
                mp[{v[i].x, v[i].y + v[j].y, v[i].z + v[j].z}] = true;
                ans--;
            }
            if (v[i].y != 0 && v[i].y == v[j].y && v[i].x != v[j].x && v[i].z != v[j].z && mp[{v[i].x + v[j].x, v[i].y, v[i].z + v[j].z}] == false) {
                mp[{v[i].x + v[j].x, v[i].y, v[i].z + v[j].z}] = true;
                ans--;
            }
            if (v[i].z != 0 && v[i].z == v[j].z && v[i].y != v[j].y && v[i].x != v[j].x && mp[{v[i].x + v[j].x, v[i].y + v[j].y, v[i].z}] == false) {
                ans--;
                mp[{v[i].x + v[j].x, v[i].y + v[j].y, v[i].z}] = true;
            }
        }
    }

    cout << ans;
}