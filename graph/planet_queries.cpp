// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;
 
int n, q, max_k;
vector<int> child;
vector<pair<int, int>> queries;
vector<vector<int>> desc;
 
int M;
 
 
// int getDescAt2i(int u, int i) {
//     if (i == 0) return child[u];
//     if (desc[i][u] != -1) return desc[i][u];
//     return desc[i][u] = getDescAt2i(getDescAt2i(u, i - 1), i - 1);
// }
 
int getDesc(int u, int k, vector<vector<int>> &desc) {
    if (u == child[u]) return u;
    if (k == 0) return u;
    for (int i = 0; i < 32; ++i) {
        int bit = k & (1 << i);
        if (bit == 0) continue;
        u = desc[u][i];
    }
    return u;
}
    
void help(vector<int> &res) {
    M = log2(max_k) + 1;
    desc = vector<vector<int>>(n, vector<int>(M + 1, -1));  
    for (int i = 0; i < M + 1; ++i) {
        for (int u = 0; u < n; ++u) {
            if (i == 0) { desc[u][i] = child[u]; continue; }
            desc[u][i] = desc[desc[u][i - 1]][i - 1];
        }
    }
    
    for (const auto &q: queries) {
        int u = q.first, k = q.second;
        res.push_back(getDesc(u, k, desc));
        // cout << "q: " << u << ", " << k << ", " << res.back() << endl;
    }
}
 
 
int main() {
    cin >> n >> q;
    child = vector<int>(n, -1);
    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        child[i] = v - 1;
    }
    max_k = 0;
    queries.clear();
    for (int i = 0; i < q; ++i) {
        int x, k;
        cin >> x >> k;
        --x;
        max_k = max(max_k, k);
        queries.push_back(make_pair(x, k));
    }
 
    vector<int> res;
    res.reserve(q);
    help(res);
    for (int x: res)
        cout << (x + 1) << "\n";
 
    return 0;
}