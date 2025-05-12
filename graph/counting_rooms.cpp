#include<bits/stdc++.h>

using namespace std;




const vector<vector<int>> dxy = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool IsSafe(int i, int j, int m, int n) {
    return i >= 0 && j >= 0 && i < m && j < n;
}

void dfs(int i, int j, vector<vector<bool>> &visited, const vector<vector<char>> &grid) {
    int m = grid.size(), n = grid[0].size();
    visited[i][j] = true;
    for (const auto &dir: dxy) {
        int x = i + dir[0], y = j + dir[1];
        if (!IsSafe(x, y, m, n) || visited[x][y] || grid[x][y] == '#') continue;
        dfs(x, y, visited, grid);
    }
}


int CountConnectedComponent(const vector<vector<char>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    int res = 0;
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (visited[i][j] || grid[i][j] == '#') continue;
            dfs(i, j, visited, grid);
            ++res;
        }
    }
    return res;
}

int main()
{
    // cout << "\n\nHello earth\n\n\n";
    int m, n;
    cin >> m >> n;
    vector<vector<char>> grid(m, vector<char>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }
    
    cout << CountConnectedComponent(grid);



    return 0;
}