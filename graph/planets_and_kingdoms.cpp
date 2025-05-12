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
 
    void get_transpose_graph(Graph &res) {
        res.n = this->n;
        res.adj = vector<vector<int>>(n);
        for (int u = 0; u < n; ++u) { for (int v: adj[u]) { res.add_edge(v, u); }}
    }
};
 
void dfs(int u, vector<bool> &visited, Graph &graph, vector<int> &nodes_in_desc_order_of_finish_time) {
    visited[u] = true;
    for (int v: graph.get_edges(u)) { if (!visited[v]) dfs(v, visited, graph, nodes_in_desc_order_of_finish_time); }
    nodes_in_desc_order_of_finish_time.push_back(u);
}
 
void dfs_assign_scc_id(int u, int curr_scc_id, vector<bool> &visited, Graph &graph, vector<int> &scc_id) {
    visited[u] = true;
    scc_id[u] = curr_scc_id;
    for (int v: graph.get_edges(u)) { if (!visited[v]) dfs_assign_scc_id(v, curr_scc_id, visited, graph, scc_id); }
}
 
pair<int, vector<int>> get_all_scc(Graph &graph) {
    vector<bool> visited(graph.V(), false);
    vector<int> nodes_in_desc_order_of_finish_time;
    nodes_in_desc_order_of_finish_time.reserve(graph.V());
    for (int u = 0; u < graph.V(); ++u) {
        if (visited[u]) continue;
        dfs(u, visited, graph, nodes_in_desc_order_of_finish_time);
    }
    reverse(nodes_in_desc_order_of_finish_time.begin(), nodes_in_desc_order_of_finish_time.end());
 
    vector<int> scc_id(graph.V(), -1);
    Graph transpose_graph(graph.V());
    graph.get_transpose_graph(transpose_graph);
    visited.assign(visited.size(), false);
    int increasing_scc_id = 0;
    for (int u: nodes_in_desc_order_of_finish_time) {
        if (visited[u]) continue;
        ++increasing_scc_id;
        dfs_assign_scc_id(u, increasing_scc_id, visited, transpose_graph, scc_id);
    }
    return {increasing_scc_id, scc_id};
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
    pair<int, vector<int>> res = get_all_scc(graph);
    cout << res.first << "\n";
    for (int ele: res.second) cout << ele << " ";
    return 0;
}