#include<bits/stdc++.h>

using namespace std;




long long mc(int i, int j, const vector<long long> &a, vector<vector<long long>> &memo) {
    if (i > j) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    long long m1 = a[i] + min(mc(i + 2, j, a, memo), mc(i + 1, j - 1, a, memo));
    long long m2 = a[j] + min(mc(i, j - 2, a, memo), mc(i + 1, j - 1, a, memo));
    return memo[i][j] = max(m1, m2);
}

long long bottom_up(const vector<long long> &a) {
    int n = a.size();
    vector<vector<long long>> mc(n + 4, vector<long long>(n + 4, -1));
    for (int i = n - 1 + 2; i >= 0 + 2; --i) {
        for (int j = 0 + 2; j < n + 2; ++j) {
                if (i > j) {
                    mc[i][j] = 0;
                    continue;
                }

                long long m1 = a[i] + min(mc[i + 2][j], mc[i + 1][j - 1]);
                long long m2 = a[j] + min(mc[i][j - 2], mc[i + 1][j - 1]);
                mc[i][j] = max(m1, m2);
        }
    }
    return mc[0 + 2][n - 1 + 2];
}

long long help_me(const vector<long long> &a) {
    return bottom_up(a);
    // int n = a.size();
    // vector<vector<long long>> memo(n, vector<long long>(n, -1));
    // return mc(0, n - 1, a, memo);
}

int main()
{
    // cout << "\n\nHello earth\n\n\n";

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    
    cout << help_me(a);

    return 0;
}