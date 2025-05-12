#include<bits/stdc++.h>
using namespace std;


class Graph {
    int n;
    vector<vector<int>> adj;
public:
    Graph(int n): n(n), adj(vector<vector<int>>(n)) {}
    int V() { return n; }
    vector<int> &get_edges(int u) { return adj[u]; }
    void add_edge(int from, int to) { adj[from].push_back(to); }
};
 

int ALL_VISITED_BITMASK = 0;
vector<vector<bool>> reachable;

bool all_visited(int visited_bitmask, int n) {
    return visited_bitmask == ALL_VISITED_BITMASK;
}

//* c(u, visited) = no. of valid path from u to (n-1)
//*                 visiting each node which are not visited, exactly once,
//*                 and not visiting the vsitied nodes again 
long long c(int u, int visited_bitmask, Graph &graph) {
    if (u == graph.V() - 1 && visited_bitmask == ALL_VISITED_BITMASK) return 1;
    for (int v = 0; v < graph.V(); ++v) {
        if ((visited_bitmask & (1 << v)) == 0 && !reachable[u][v])
            return 0;
    }

    long long res = 0;
    for (int v: graph.get_edges(u)) {
        //* if visited
        if ((visited_bitmask & (1 << v)) != 0) continue;
        res += c(v, visited_bitmask | (1 << v), graph);
    }
    return res;
}


bool dfs(int u, int dest, vector<bool> &visited, Graph &g) {
    if (u == dest) return true;
    visited[u] = true;
    for (int v: g.get_edges(u)) if (dfs(v, dest, visited, g)) return true;
    return false;
}

long long help(Graph &graph) {
    ALL_VISITED_BITMASK = pow(2, graph.V()) - 1;
    reachable = vector<vector<bool>>(graph.V(), vector<bool>(graph.V()));
    for (int u = 0; u < graph.V(); ++u) {
        for (int v = 0; v < graph.V(); ++v) {
            vector<bool> visited(graph.V(), false);
            reachable[u][v] = dfs(u, v, visited, graph);
        }
    }
    return c(0, 1, graph);
}

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        graph.add_edge(u - 1, v - 1);
    }
    cout << help(graph);
    return 0;
}