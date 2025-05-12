#include<bits/stdc++.h>

using namespace std;


const unordered_map<char, vector<int>> dxy = {
    {'R', {0, 1}},
    {'L', {0, -1}},
    {'D', {1, 0}},
    {'U', {-1, 0}},
};

bool IsSafe(int i, int j, int m, int n) {
    return i >= 0 && j >= 0 && i < m && j < n;
}

bool IsDest(int i, int j, int m, int n) {
    return i == 0 || i == m - 1 || j == 0 || j == n - 1;
}


pair<string, string> help(const vector<vector<char>> &grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> monster_reach_time(m, vector<int>(n, INT_MAX));
    queue<pair<int, int>> q;
    pair<int, int> start = {-1, -1};
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'M') {
                monster_reach_time[i][j] = 0;
                q.push(make_pair(i, j));
            } else if (grid[i][j] == 'A') {
                start = {i, j};
            }
        }
    }
    int curr_level = 0;
    while (q.size()) {
        int curr_level_size = q.size();
        while (curr_level_size--) {
            pair<int, int> u = q.front();
            q.pop();
    
            for (const auto &dir: dxy) {
                int x = u.first + dir.second[0], y = u.second + dir.second[1];
                if (!IsSafe(x, y, m, n) || grid[x][y] == '#' 
                    || monster_reach_time[x][y] != INT_MAX) 
                    continue;
                
                monster_reach_time[x][y] = 1 + curr_level;
                q.push({x, y});
            }
        }
        ++curr_level;
    }


    vector<vector<int>> hero_reach_time(m, vector<int>(n, INT_MAX));
    //* hero must traverse through cells where the time for hero to reach that cell 
    //* should be < time for any monster to reach that cell
    vector<vector<pair<int, int>>> parent(m, vector<pair<int, int>>(n, {-1, -1}));
    vector<vector<char>> parent_dir(m, vector<char>(n, '#'));
    q.push(start);
    hero_reach_time[start.first][start.second] = 0;
    curr_level = 0;
    pair<int, int> dest_cell = {-1, -1};
    while (q.size()) {
        int curr_level_size = q.size();
        while (curr_level_size--) {
            pair<int, int> u = q.front();
            q.pop();
    
            if (IsDest(u.first, u.second, m, n)) {
                dest_cell = u;
                break;
            } 

            for (const auto &dir: dxy) {
                char dir_letter = dir.first;
                int x = u.first + dir.second[0], y = u.second + dir.second[1];
                int curr_cell_hero_reach_time = curr_level + 1;
                if (!IsSafe(x, y, m, n) || grid[x][y] != '.' 
                    || hero_reach_time[x][y] != INT_MAX
                    || monster_reach_time[x][y] <= curr_cell_hero_reach_time) 
                    continue;
                
                q.push({x, y});
                hero_reach_time[x][y] = curr_cell_hero_reach_time;
                parent[x][y] = u;
                parent_dir[x][y] = dir_letter;
            }
        }
        ++curr_level;
    } 
    if (dest_cell.first == -1) return {"NO", ""};
    string res_path;
    pair<int, int> curr_cell = dest_cell;
    while (parent[curr_cell.first][curr_cell.second].first != -1) {
        res_path.push_back(parent_dir[curr_cell.first][curr_cell.second]);
        curr_cell = parent[curr_cell.first][curr_cell.second];
    }
    reverse(res_path.begin(), res_path.end());
    return {
        "YES",
        res_path
    };
}

int main() {
    // cout << "\n\nHello earth\n\n\n";
    int m, n;
    cin >> m >> n;
    vector<vector<char>> grid(m, vector<char>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }
    
    pair<string, string> res = help(grid);
    cout << res.first;

    if (res.first == "YES") {
        cout << "\n" << res.second.size() << "\n" << res.second;
    }

    return 0;
}